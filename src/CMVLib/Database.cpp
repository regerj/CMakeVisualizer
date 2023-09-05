#include "Database.h"

#include <cstdint>
#include <map>
#include <vector>

#include "Node.h"

namespace CMV {

void Database::Insert(Node node) {
    m_nodes.push_back(node);
    m_map.insert(std::pair<std::string, int>(node.name, m_nodes.size() - 1));
}

bool Database::Exists(std::string name) {
    return m_map.find(name) != m_map.end() ? true : false;
}

Node Database::operator[](uint32_t index) const {
    return m_nodes[index];
}

Node &Database::operator[](uint32_t index) {
    return m_nodes[index];
}

Node Database::operator[](std::string name) const {
    return m_nodes[m_map.at(name)];
}

Node &Database::operator[](std::string name) {
    return m_nodes[m_map.at(name)];
}

void Database::GenerateAdjacencyMatrix() {
    m_adjacencyMatrix.resize(m_nodes.size());
    for (auto &vector : m_adjacencyMatrix) {
        vector.resize(m_nodes.size());
    }
    for (auto &node : m_nodes) {
        for (const auto &link : m_nodes[m_map.at(node.name)].links) {
            
        }
    }
}

std::vector<Node> Database::GetNodes() {
    return m_nodes;
}

} // namespace CMV