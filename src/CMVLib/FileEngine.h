#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_set>

#include "Database.h"
#include "Node.h"

namespace CMV {

class FileEngine {
    public:
        FileEngine(Database graph);
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
        Database m_graph;
};

} // namespace CMV