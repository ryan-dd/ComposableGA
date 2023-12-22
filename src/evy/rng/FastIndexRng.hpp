#ifndef EVY_FAST_INDEX_RNG_HPP
#define EVY_FAST_INDEX_RNG_HPP

#include "evy/rng/prng/xoshiro256ss.hpp"
#include "evy/rng/distributions/IntMult.hpp"

namespace evy
{

class FastIndexRng
{
private:
  Xoshiro256ss rng{};
  IntMult intMult;
public:
  explicit FastIndexRng(std::size_t max):
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
