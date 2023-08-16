#pragma once

#include <map>
#include <string>

#include "CMakeNode.h"

namespace CMakeNode {

class FileEngine {
    public:
        FileEngine(std::map<std::string, Node> nodes);
        void Generate();
        ~FileEngine();
    protected:
        std::map<std::string, Node> m_nodes;
};

} // namespace CMakeNode