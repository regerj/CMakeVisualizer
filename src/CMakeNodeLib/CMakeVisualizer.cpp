#include "CMakeVisualizer.h"

#include <fstream>
#include <string>

namespace CMakeNode {

FileEngine::FileEngine(std::map<std::string, Node> nodes) : m_nodes{nodes} {}

FileEngine::~FileEngine() {}

void FileEngine::Generate() {
    std::ofstream outFile("graph.gv");
    outFile << "digraph G {\n";
    outFile << "    splines=\"FALSE\";\n";

    for (const auto &node : m_nodes) {
        outFile << "    " << node.second.name << " [label=\"" << node.second.name << "\", shape=\"square\"];\n";
    }

    for (const auto &node : m_nodes) {
        for (const auto &link : node.second.links) {
            outFile << "    " << link << " -> " << node.second.name << ";\n";
        }
    }

    outFile << "}";

    outFile.close();
}

} // namespace CMakeNode