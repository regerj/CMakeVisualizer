#pragma once
#include <string>
#include <vector>

namespace CMakeNode {

enum NodeType {
    BINARY = 0,
    LIBRARY
};

enum NodeScope {
    INTERNAL = 0,
    EXTERNAL
};

struct Node {
    std::string name;
    NodeType type;
    NodeScope scope;
    std::vector<std::string> links;
    std::vector<std::string> sources;
};

} // namespace CMakeNode
