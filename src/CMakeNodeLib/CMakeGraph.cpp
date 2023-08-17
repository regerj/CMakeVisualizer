#include "CMakeGraph.h"

#include <cstdint>
#include <map>
#include <vector>

#include "CMakeNode.h"

namespace CMakeNode {

void CMakeGraph::Insert(Node node) {
    m_nodes.push_back(node);
    m_map[node.name] = m_nodes.size() - 1;
}

bool CMakeGraph::Exists(std::string name) {
    return m_map.find(name) != m_map.end() ? true : false;
}

Node CMakeGraph::operator[](uint32_t index) const {
    return m_nodes[index];
}

Node &CMakeGraph::operator[](uint32_t index) {
    return m_nodes[index];
}

Node CMakeGraph::operator[](std::string name) const {
    return m_nodes[m_map.at(name)];
}

Node &CMakeGraph::operator[](std::string name) {
    return m_nodes[m_map.at(name)];
}

void CMakeGraph::GenerateAdjacencyMatrix() {
    m_adjacencyMatrix.resize(m_nodes.size());
    for (auto &vector : m_adjacencyMatrix) {
        vector.resize(m_nodes.size());
    }
    for (auto &node : m_nodes) {
        for (const auto &link : m_nodes[m_map.at(node.name)].links) {
            
        }
    }
}

} // namespace CMakeNode