add_executable(CMV)

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

add_subdirectory(CMakeNodeLib)