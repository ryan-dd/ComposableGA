add_library(ComposableGAlib
    strategies/DefaultCrossover.cpp
    strategies/DefaultEvaluator.cpp
    strategies/DefaultInitialSolutionGenerator.cpp
    strategies/DefaultMutator.cpp
    strategies/K_TournamentParentSelector.cpp
    Parameter.cpp
    DefaultGA.cpp
)

target_link_libraries(ComposableGAlib PUBLIC CONAN_PKG::entt)
target_include_directories(ComposableGAlib PUBLIC 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/include/strategies
)
target_compile_options(ComposableGAlib INTERFACE ${PROJECT_WARNINGS})
