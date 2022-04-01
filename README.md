# ComposableGA
A C++ library for genetic algorithm optimization using ECS (entity component system) to represent parameters.
Designed to:
1. Make it easy to swap out mutation, crossover, and selection strategies
2. Make it easy to use heterogeneous parameters in objective function without modification to strategies.

## Build requirements

Cmake and Conan
## To build


`conan install . -if build`

`cmake -S . -B build`

`cmake --build build`
