#ifndef EVVY_INT_MULT_H
#define EVVY_INT_MULT_H

#include <cstdint>

class IntMult
{
private:
  std::uint32_t upperLimit;

public:
  IntMult(std::uint32_t upperLimit):
    upperLimit(upperLimit)
  {}
  // Int multiply
  template<typename Rng>
  std::uint32_t operator()(Rng& rng) 
  {
    std::uint32_t x = rng();
    std::uint64_t m = std::uint64_t(x) * std::uint64_t(upperLimit);
    return m >> 32;
  }

};

#endif
