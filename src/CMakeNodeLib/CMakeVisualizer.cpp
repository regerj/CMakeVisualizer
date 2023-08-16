#include "CMakeVisualizer.h"

#include <deque>
#include <fstream>
#include <string>
#include <unordered_set>

namespace CMakeNode {

FileEngine::FileEngine(std::map<std::string, Node> nodes) : m_nodes{nodes} {}

FileEngine::~FileEngine() {}

void FileEngine::Generate() {
    for (const auto &node : m_nodes) {
        std::ofstream outFile(node.second.name + "graph.gv");
        outFile << "digraph G {\n";
        outFile << "    splines=\"TRUE\";\n";
        
        RecursiveNodeAddition(outFile, node.second);
        RecursiveEdgeAddition(outFile, node.second);

        outFile << "}";

        outFile.close();
    }
}


void FileEngine::RecursiveNodeAddition(std::ofstream &outFile, const Node node, std::unique_ptr<std::unordered_set<std::string>> visited) {
    // Mark as visited
    visited->insert(node.name);
    outFile << "    " << node.name << " [label=\"" << node.name << "\", shape=\"square\"];\n";

    for (const auto &iter : node.links) {
        // If it has already been visited or if it is a leaf node
        if (visited->find(iter) == visited->end() && m_nodes.find(iter) != m_nodes.end()) {
            RecursiveNodeAddition(outFile, m_nodes.find(iter)->second, std::move(visited));
        }
    }
}

void FileEngine::RecursiveEdgeAddition(std::ofstream &outFile, const Node node, std::unique_ptr<std::unordered_set<std::string>> visited) {
    visited->insert(node.name);

    for (const auto &iter : node.links) {
        if (visited->find(iter) == visited->end() && m_nodes.find(iter) != m_nodes.end()) {
            outFile << "    " << iter << " -> " << node.name << ";\n";
            RecursiveEdgeAddition(outFile, m_nodes.find(iter)->second, std::move(visited));
        }
    }
}

} // namespace CMakeNode