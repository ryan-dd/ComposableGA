cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 14)

project(EvolutionaryAlgorithms)
set(CMAKE_BUILD_TYPE Debug)

add_executable(EvolutionaryAlgorithms src/main.cpp)
add_library(EvoAlgo src/OptimizationProblem.cpp src/OptimizationProblem.hpp)

target_include_directories(EvolutionaryAlgorithms PUBLIC src)
target_link_libraries(EvolutionaryAlgorithms PUBLIC EvoAlgo)