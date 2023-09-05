add_executable(CMakeVisualizer)

target_link_libraries(
    CMakeVisualizer
    PUBLIC
    CMV
)

target_sources(
    CMakeVisualizer
    PRIVATE
    main.cpp
)

add_subdirectory(CMVLib)