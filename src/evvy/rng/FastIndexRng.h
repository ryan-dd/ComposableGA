#ifndef EVVY_FAST_INDEX_RNG_H
#define EVVY_FAST_INDEX_RNG_H

#include "prng/xoshiro256ss.h"
#include "distributions/IntMult.h"

namespace evvy
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
