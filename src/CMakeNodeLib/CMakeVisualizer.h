#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_set>

#include "CMakeNode.h"

namespace CMakeNode {

class FileEngine {
    public:
        FileEngine(std::map<std::string, Node> nodes);
        void Generate();
        ~FileEngine();
    protected:
        void RecursiveNodeAddition(
            std::ofstream &outFile,
            const Node node,
            std::unique_ptr<std::unordered_set<std::string>> visited = std::make_unique<std::unordered_set<std::string>>()
        );
        void RecursiveEdgeAddition(
            std::ofstream &outFile,
            const Node node,
            std::unique_ptr<std::unordered_set<std::string>> visited = std::make_unique<std::unordered_set<std::string>>()
        );
        std::map<std::string, Node> m_nodes;
};

} // namespace CMakeNode