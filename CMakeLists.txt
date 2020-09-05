cmake_minimum_required (VERSION 3.10)
set (CMAKE_CXX_STANDARD 14)

project(EvolutionaryAlgorithms)
set(CMAKE_BUILD_TYPE Debug)

add_executable(EvolutionaryAlgorithms src/main.cpp)
add_library(EvoAlgo src/OptimizationProblem.cpp src/OptimizationProblem.hpp)

target_include_directories(EvolutionaryAlgorithms PUBLIC src)
target_link_libraries(EvolutionaryAlgorithms PUBLIC EvoAlgo)

# Add tests
add_subdirectory(extern/googletest)
enable_testing()

add_executable(runTests test/opti_problem_test.cpp)
target_include_directories(runTests PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(runTests PUBLIC gtest gtest_main pthread)
target_include_directories(runTests PUBLIC src)
target_link_libraries(runTests PUBLIC EvoAlgo)
add_test(NAME runTests COMMAND testDriver)


