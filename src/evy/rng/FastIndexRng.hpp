#ifndef EVY_FAST_INDEX_RNG_HPP
#define EVY_FAST_INDEX_RNG_HPP

#include "prng/xoshiro256ss.hpp"
#include "distributions/IntMult.hpp"

namespace evy
{

class FastIndexRng
{
private:
  Xoshiro256ss rng{};
  IntMult intMult;
public:
  FastIndexRng(std::size_t max):
    rng{},
    intMult(max)
  {
  }

  decltype(intMult(rng)) operator()()
  {
    return intMult(rng);
  }
};
}

#endif
