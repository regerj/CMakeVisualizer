add_executable(CMV)
add_library(empty)

target_link_libraries(
    CMV
    PUBLIC
    CMakeNode
)

target_sources(
    CMV
    PRIVATE
    main.cpp
)

target_sources(
    empty
    PRIVATE
    empty.cpp
)

add_subdirectory(CMakeNodeLib)