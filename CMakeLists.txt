cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 14)

project(EvolutionaryAlgorithms)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)

add_subdirectory(extern/googletest)
enable_testing()
add_subdirectory(test)

