add_library(CMakeNode)

target_include_directories(
    CMakeNode
    PUBLIC
    .
)

target_sources(
    CMakeNode
    PRIVATE
    CMakeGraph.cpp
    CMakeNode.cpp
    CMakeParser.cpp
    CMakeVisualizer.cpp
)