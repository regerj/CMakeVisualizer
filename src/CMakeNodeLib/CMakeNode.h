#include <string>
#include <vector>

namespace CMakeNode {

struct Node {
    std::string name;
    std::vector<Node> connections;
    std::vector<std::string> sources;
};

// class Node {
//     public:
//         Node();
//         Node(std::string name, std::vector<Node> connections);
//         ~Node();
//     protected:
//         std::string m_name = "";
//         std::vector<Node> m_connections;
//         std::vector<std::string> m_sourceFiles;
// };

} // namespace CMakeNode
