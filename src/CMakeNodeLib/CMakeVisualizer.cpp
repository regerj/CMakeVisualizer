#include "CMakeVisualizer.h"

#include <deque>
#include <fstream>
#include <string>
#include <unordered_set>

namespace CMakeNode {

FileEngine::FileEngine(CMakeGraph graph) : m_graph{graph} {}

FileEngine::~FileEngine() {}

void FileEngine::Generate() {
    for (const auto &node : m_graph.GetNodes()) {
        std::ofstream outFile(node.name + "graph.gv");
        outFile << "digraph G {\n";
        outFile << "    splines=\"TRUE\";\n";
        
        RecursiveNodeAddition(outFile, node);
        RecursiveEdgeAddition(outFile, node);

        outFile << "}";
        outFile.close();
    }
}


void FileEngine::RecursiveNodeAddition(std::ofstream &outFile, const Node node, std::shared_ptr<std::unordered_set<std::string>> visited) {
    // Mark as visited
    visited->insert(node.name);
    // Wrapping the name in quotes prevents DOT from getting pissy about '::' in things like "GTest::Gtest"
    outFile << "    " << "\"" << node.name << "\"" << " [label=\"" << node.name << "\", shape=\"square\"];\n";

    for (const auto &iter : node.links) {
        // Check if it has been visited before and make sure it exists in the graph
        if (visited->find(iter) == visited->end() && m_graph.Exists(iter)) {
            RecursiveNodeAddition(outFile, m_graph[iter], visited);
        }
    }
}

void FileEngine::RecursiveEdgeAddition(std::ofstream &outFile, const Node node, std::shared_ptr<std::unordered_set<std::string>> visited) {
    visited->insert(node.name);

    for (const auto &iter : node.links) {
        // Check if it has been visited before and make sure it exists in the graph
        if (visited->find(iter) == visited->end() && m_graph.Exists(iter)) {
            // Wrapping the names in quotes prevents DOT from getting pissy about '::' in things like "GTest::Gtest"
            outFile << "    " << "\"" << iter << "\"" << " -> " << "\"" << node.name << "\"" << ";\n";
            RecursiveEdgeAddition(outFile, m_graph[iter], visited);
        }
    }
}

} // namespace CMakeNode