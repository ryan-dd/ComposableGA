cmake_minimum_required(VERSION 3.1)

add_executable(GA_ECS main.cpp 
strategies/DefaultCrossover.cpp
strategies/DefaultEvaluator.cpp
strategies/DefaultInitialSolutionGenerator.cpp
strategies/DefaultMutator.cpp
strategies/K_TournamentParentSelector.cpp
Parameter.cpp
)

target_link_libraries(GA_ECS PUBLIC CONAN_PKG::entt)
target_include_directories(GA_ECS PRIVATE 
${CMAKE_SOURCE_DIR}/include 
${CMAKE_SOURCE_DIR}/include/strategies)

target_compile_options(GA_ECS INTERFACE ${PROJECT_WARNINGS})
