# Evy

A header-only, composable evolutionary algorithm toolkit taking advantage of the latest C++23 features. See `examples` for more details and documentation.

Out of the box, supports running genetic algorithm with custom aggregate types and objective functions. Heavily depends on concepts and templates to avoid any inheritance boilerplate code and allow for customization flexibility.

# Dependencies

Depends on header-only [__boost::pfr__](https://github.com/boostorg/pfr) (aka magic\_get) to facilitate accessing each member variable of a aggregate by numbered index (hopefully this will be in the standard library eventually, see [P2141](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2141r0.html))

