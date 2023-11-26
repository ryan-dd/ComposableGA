# Evy

A header-only, composable evolutionary algorithm toolkit taking advantage of the latest C++23 features. See `examples` for more details and documentation.

Out of the box, supports running genetic algorithm with custom aggregate types and objective functions. Heavily depends on concepts and templates to avoid any inheritance boilerplate code and allow for customization flexibility.

# Dependencies

Depends on header-only [__boost::pfr__](https://github.com/boostorg/pfr) (aka magic\_get) to facilitate accessing each member variable of a aggregate by numbered index (hopefully this will be in the standard library eventually, see [P2141](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2141r0.html))

# Genetic Algorithm Tutorial

A genetic algorithm is the most common evolutionary algorithm. You can read more [here](https://en.wikipedia.org/wiki/Genetic_algorithm) about what it entails. Its main purpose is to maximize some fitness function, also known as the objective function. It uses selection, crossover, and mutation to do this. Currently, helper functions for a genetic algorithm are defined to perform selection, crossover, and mutation. 

## Rosenbrock example

Using a Rosenbrock function as an example, the objective function would be defined as follows:

https://github.com/ryan-dd/evy/blob/b6053bc1972dc9e240e3a87d46a5a779ddd618b6/examples/Rosenbrock.cpp#L20C1-L41C2

Notice how no inheritance of base classes are required, just simply declaring and using types and functions.
