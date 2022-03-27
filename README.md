# Composable GA
A C++ library for genetic algorithm using the entity component system (ECS) to represent parameters.

Assumes parameters are independent and that changing the value of one parameter will not invalidate another parameter (for now).

# To build
conan install . -if build
cmake -S . -B build
cmake --build build