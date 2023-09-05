// stl/linux
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

// My libs
#include <Node.h>
#include <Parser.h>
#include <FileEngine.h>

// Because thats just obnoxious
namespace fs = std::filesystem;

int main() {
    CMV::Parser parser("/home/kalidev/src/cmake-example");
    parser.Parse();
    auto graph = parser.GetGraph();

    // Print it for debug
    // auto nodes = graph.GetNodes();
    // for (const auto &node : nodes) {
    //     std::cout << "Target: " << node.name << std::endl;
    //     std::cout << "\tLinks:" << std::endl;
    //     for (const auto &link : node.links) {
    //         std::cout << "\t\t" << link << std::endl;
    //     }
    //     std::cout << "\tSources:" << std::endl;
    //     for (const auto &source : node.sources) {
    //         std::cout << "\t\t" << source << std::endl;
    //     }
    // }

    CMV::FileEngine engine(graph);
    engine.Generate();
}