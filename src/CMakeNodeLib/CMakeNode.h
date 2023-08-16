#pragma once
#include <string>
#include <vector>

namespace CMakeNode {

enum NodeType {
    BINARY = 0,
    LIBRARY
};

struct Node {
    std::string name;
    NodeType type;
    std::vector<std::string> links;
    std::vector<std::string> sources;
};

} // namespace CMakeNode
