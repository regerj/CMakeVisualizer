#pragma once
#include <string>
#include <vector>

namespace CMakeNode {

struct Node {
    std::string name;
    std::vector<std::string> links;
    std::vector<std::string> sources;
};

} // namespace CMakeNode
