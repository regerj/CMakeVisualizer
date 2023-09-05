#include "FileEngine.h"

#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unordered_set>

namespace CMV {

FileEngine::FileEngine(Database graph) : m_graph{graph} {}

FileEngine::~FileEngine() {}

void FileEngine::Generate() {
    int status = 0;
    struct stat sb{0};
    status = stat("./graph", &sb);
    if (status != 0) {
        status = mkdir("./graph", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (status != 0) {
            throw std::runtime_error("Failed to find, access, or create the graph directory.");
        }
    }
    
    for (const auto &node : m_graph.GetNodes()) {
        std::ofstream outFile("./graph/" + node.name + "graph.gv");
        outFile << "digraph G {\n";
        outFile << "    splines=\"TRUE\";\n";
        
        RecursiveNodeAddition(outFile, node);
        RecursiveEdgeAddition(outFile, node);

        outFile << "}";
        outFile.close();

        system(std::string("dot -Tpng ./graph/" + node.name + "graph.gv -o ./graph/" + node.name + ".png").c_str());
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

} // namespace CMV