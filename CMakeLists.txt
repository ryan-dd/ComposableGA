cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 20)

project(EvolutionaryAlgorithms)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_subdirectory(src)
add_subdirectory(src2)

add_subdirectory(extern/googletest)
enable_testing()
add_subdirectory(test)

