add_library(CMV)

target_include_directories(
    CMV
    PUBLIC
    .
)

target_sources(
    CMV
    PRIVATE
    Node.cpp
    Parser.cpp
    FileEngine.cpp
    Database.cpp
)