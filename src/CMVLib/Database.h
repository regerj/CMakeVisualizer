#pragma once

#include <cstdint>
#include <map>
#include <vector>

#include "Node.h"

namespace CMV {

class Database {
    public:
        Database() {}
        ~Database() {}

        std::vector<Node> GetNodes();

        void Insert(Node node);

        bool Exists(std::string name);

        Node operator[](uint32_t index) const;
        Node &operator[](uint32_t index);

        Node operator[](std::string name) const;
        Node &operator[](std::string name);
    private:
        std::vector<Node> m_nodes;
        std::map<std::string, int> m_map;
};

} // namespace CMV