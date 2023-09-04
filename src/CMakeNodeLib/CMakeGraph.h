#pragma once

#include <cstdint>
#include <map>
#include <vector>

#include "CMakeNode.h"

namespace CMakeNode {

class CMakeGraph {
    public:
        CMakeGraph() {}
        ~CMakeGraph() {}

        std::vector<Node> GetNodes();

        void Insert(Node node);

        void GenerateAdjacencyMatrix();

        bool Exists(std::string name);

        Node operator[](uint32_t index) const;
        Node &operator[](uint32_t index);

        Node operator[](std::string name) const;
        Node &operator[](std::string name);
    private:
        std::vector<std::vector<bool>> m_adjacencyMatrix;
        std::vector<Node> m_nodes;
        std::map<std::string, int> m_map;
};

} // namespace CMakeNode