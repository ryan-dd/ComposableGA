#ifndef EVY_XOSHIRO_256SS_HPP
#define EVY_XOSHIRO_256SS_HPP

#include <cstdint>
#include <random>
#include <span>

class Xoshiro256ss
{
public:
  Xoshiro256ss()
  {
    std::random_device rd;
    std::span stateSpan(state);
    for(auto& statePart: stateSpan)
    {
      statePart = rd();
    }
  }

  uint64_t operator()()
  {
      uint64_t x = state[1] * 5;
      uint64_t r = ((x << 7) | (x >> 57)) * 9;
      uint64_t t = state[1] << 17;
      state[2] ^= state[0];
      state[3] ^= state[1];
      state[1] ^= state[2];
      state[0] ^= state[3];
      state[2] ^= t;
      state[3] = (state[3] << 45) | (state[3] >> 19);
      return r;
  }

  // Functions to allow to be used with std library number generators
  using result_type = uint64_t;

  static constexpr result_type min()
  {
    return 0;
  }

  static constexpr result_type max()
  {
    return std::numeric_limits<result_type>::max();
  }

private:
  uint64_t state[4];
};

#endif
