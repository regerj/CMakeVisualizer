#pragma once

#include <filesystem>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "CMakeGraph.h"
#include "CMakeNode.h"

namespace CMakeNode {

class CMakeParser {
    public:
        CMakeParser();
        CMakeParser(std::string path);
        CMakeParser * Parse();
        std::map<std::string, Node> GetNodes();
        CMakeGraph GetGraph();
    protected:
        void ParseForTargets(std::filesystem::path path);
        void ParseForSources(std::filesystem::path path);
        void ParseForLinks(std::filesystem::path path);
        std::vector<std::string> Tokenize(const std::string &str);
        std::vector<std::string> ParseWithRegex(const std::string str, const std::regex &rx);
        std::string ReadFile(std::filesystem::path path);
        std::string m_path;
        std::map<std::string, Node> m_nodes;
        CMakeGraph m_graph;
        const std::regex m_targetRegex = std::regex("add_(executable|library)\\([^\\)]*\\)");
        const std::regex m_sourceRegex = std::regex("target_sources\\([^\\)]*\\)");
        const std::regex m_linksRegex = std::regex("target_link_libraries\\([^\\)]*\\)");
        const std::regex m_whitespaceRegex = std::regex("([\\n|\\s]+)");
};

} // namespace CMakeNode