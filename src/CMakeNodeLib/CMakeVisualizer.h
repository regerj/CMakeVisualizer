#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_set>

#include "CMakeGraph.h"
#include "CMakeNode.h"

namespace CMakeNode {

class FileEngine {
    public:
        FileEngine(CMakeGraph graph);
        void Generate();
        ~FileEngine();
    protected:
        void RecursiveNodeAddition(
            std::ofstream &outFile,
            const Node node,
            std::shared_ptr<std::unordered_set<std::string>> visited = std::make_shared<std::unordered_set<std::string>>()
        );
        void RecursiveEdgeAddition(
            std::ofstream &outFile,
            const Node node,
            std::shared_ptr<std::unordered_set<std::string>> visited = std::make_shared<std::unordered_set<std::string>>()
        );
        CMakeGraph m_graph;
};

} // namespace CMakeNode