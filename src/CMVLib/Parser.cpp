#include "Parser.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <vector>

#include "Database.h"
#include "Node.h"

namespace CMV {

Parser::Parser() : m_path{"./"} {

}

Parser::Parser(std::string path) : m_path{path} {

}

Parser * Parser::Parse() {
    for (const auto & entry : std::filesystem::recursive_directory_iterator(m_path)) {
        if (entry.path().string().find("CMakeLists.txt") != std::string::npos) {
            ParseForTargets(entry.path());
            ParseForLinks(entry.path());
            ParseForSources(entry.path());
        }
    }
    return this;
}

std::map<std::string, Node> Parser::GetNodes() {
    return m_nodes;
}

Database Parser::GetGraph() {
    return m_graph;
}

std::vector<std::string> Parser::ParseWithRegex(const std::string str, const std::regex &rx) {
    std::vector<std::string> vec;

    const auto wordsBegin = std::sregex_iterator(str.begin(), str.end(), rx);
    const auto wordsEnd = std::sregex_iterator();

    for (std::sregex_iterator iter = wordsBegin; iter != wordsEnd; iter++) {
        const std::string foundString = (*iter).str();
        const size_t contentsStartIndex = foundString.find('(') + 1;
        const size_t contentsEndIndex = foundString.find(')');
        const std::string contents = foundString.substr(contentsStartIndex, contentsEndIndex - contentsStartIndex);
        vec.push_back(contents);
    }
    return vec;
}

void Parser::ParseForTargets(std::filesystem::path path){
    const std::string fileContents = ReadFile(path);
    
    auto names = ParseWithRegex(fileContents, m_targetRegex);

    for (const auto &name : names) {
        std::string trimmedName = Tokenize(name)[0];
        if (m_graph.Exists(trimmedName)) {
            m_graph[trimmedName].scope = INTERNAL;
        } else {
            m_graph.Insert(Node{.name = trimmedName, .scope = INTERNAL});
        }
    }
}

void Parser::ParseForSources(std::filesystem::path path) {
    const std::string fileContents = ReadFile(path);
    
    auto sourceGroups = ParseWithRegex(fileContents, m_sourceRegex);

    for (const auto &group : sourceGroups) {
        auto sources = Tokenize(group);
        std::string target = sources[0];
        for (size_t i = 1; i < sources.size(); i++) {
            if (sources[i] == "PRIVATE" || sources[i] == "PUBLIC") {
                continue;
            }
            m_graph[target].sources.push_back(sources[i]);
        }
    }
}

void Parser::ParseForLinks(std::filesystem::path path) {
    const std::string fileContents = ReadFile(path);

    auto linkGroups = ParseWithRegex(fileContents, m_linksRegex);

    for (const auto &group : linkGroups) {
        auto links = Tokenize(group);
        std::string target = links[0];
        for (size_t i = 1; i < links.size(); i++) {
            if (links[i] == "PRIVATE" || links[i] == "PUBLIC") {
                continue;
            }
            if (!m_graph.Exists(links[i])) {
                m_graph.Insert(Node{.name = links[i], .type = LIBRARY, .scope = EXTERNAL});
            }
            m_graph[target].links.push_back(links[i]);
        }
    }
}

std::vector<std::string> Parser::Tokenize(const std::string &str) {
    std::sregex_token_iterator it{str.begin(), str.end(), m_whitespaceRegex, -1};
    std::vector<std::string> tokenized{it, {}};
    tokenized.erase(
        std::remove_if(
            tokenized.begin(),
            tokenized.end(),
            [](std::string const &s) {
                return s.size() == 0;
            }
        ),
        tokenized.end()
    );
    return tokenized;
}

std::string Parser::ReadFile(std::filesystem::path path) {
    std::ifstream file;
    file.open(path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();

    return buffer.str();
}

} // namespace CMV