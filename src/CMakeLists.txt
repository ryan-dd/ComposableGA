cmake_minimum_required(VERSION 3.1)

add_executable(EvolutionaryAlgorithms main.cpp)
add_library(EvoAlgo 
OptimizationProblem.cpp 
GeneticAlgorithm.cpp 
OptimizationProblem.hpp 
GeneticAlgorithm.hpp)

#target_include_directories(EvolutionaryAlgorithms PUBLIC src)
target_link_libraries(EvolutionaryAlgorithms PUBLIC EvoAlgo)
