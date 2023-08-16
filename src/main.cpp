#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

#include <CMakeNode.h>
#include <CMakeParser.h>
#include <CMakeVisualizer.h>

namespace fs = std::filesystem;

int main() {
    CMakeNode::CMakeParser parser("./");
    auto nodes = parser.Parse()->GetNodes();

    for (const auto &node : nodes) {
        std::cout << "Target: " << node.second.name << std::endl;
        std::cout << "\tLinks:" << std::endl;
        for (const auto &link : node.second.links) {
            std::cout << "\t\t" << link << std::endl;
        }
        std::cout << "\tSources:" << std::endl;
        for (const auto &source : node.second.sources) {
            std::cout << "\t\t" << source << std::endl;
        }
    }

    CMakeNode::FileEngine engine(nodes);
    engine.Generate();

    // Recursivley iterate the file system
    // for (const auto & entry : fs::recursive_directory_iterator("/home/kalidev/src/CMakeVisualizer/src")) {
    //     // Find every CMakeLists.txt
    //     if (entry.path().string().find("CMakeLists.txt") != std::string::npos) {
    //         std::ifstream file;
    //         file.open(entry.path());
    //         std::stringstream buffer;
    //         buffer << file.rdbuf();

    //         file.close();

    //         std::string bufferString = buffer.str();

    //         std::string pattern("add_(executable|library)\\(.*\\)");
    //         std::regex rx(pattern);

    //         auto words_begin = std::sregex_iterator(bufferString.begin(), bufferString.end(), rx);
    //         auto words_end = std::sregex_iterator();
    //         for (std::sregex_iterator i = words_begin; i != words_end; i++) {
    //             std::smatch match = *i;
    //             std::string match_str = match.str();
    //             size_t startIndex = match_str.find('(') + 1;
    //             size_t endIndex = match_str.find(')', startIndex);
    //             std::string name = match_str.substr(startIndex, endIndex - startIndex);
    //             std::cout << name << std::endl;
    //         }
    //     }
    // }
}