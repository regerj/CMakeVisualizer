#include <iostream>

#include <CMakeNode.h>

int main() {
    CMakeNode::Node node;
    node.name = "TestNode";
    std::cout << "Hello world " << node.name << std::endl;
}