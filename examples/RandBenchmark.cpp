#include <chrono>
#include <cstdint>
#include <iostream>
#include <array>

#include <limits>
#include <random>
#include <algorithm>
#include <vector>

class jsf32
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;

  static inline uint32_t rot(uint32_t x, uint32_t k) noexcept { return (((x) << (k)) | ((x) >> (32 - (k)))); }
public:
  explicit jsf32(uint32_t seed = 0xdeadbeef) noexcept
  {
    a = 0xf1ea5eed;
    b = c = d = seed;
    for(size_t i = 0; i < 20; ++i)
      (*this)();
  }

  inline uint32_t operator()() noexcept
  {
    uint32_t e = a - rot(b, 27);
    a = b ^ rot(c, 17);
    b = c + d;
    c = d + e;
    d = e + a;
    return d;
  }

  using result_type = uint32_t;

  static constexpr result_type min()
  {
    return 0;
  }

  static constexpr result_type max()
  {
    return 0xFFFFFFFFu;
  }
};

class Xoshiro256ss
{
public:
  Xoshiro256ss()
  {
    std::random_device rd;
    state[0] = rd();
    state[1] = rd();
    state[2] = rd();
    state[3] = rd();
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

  // Functions to satisfy std::uniform_random_bit_generator
  using result_type = uint64_t;

  static constexpr result_type min()
  {
    return std::numeric_limits<result_type>::min();
  }

  static constexpr result_type max()
  {
    return std::numeric_limits<result_type>::max();
  }

private:
  uint64_t state[4];
};


// Generates number between 0 and upper_limit
// takes 32 bit RNG as input
class IntMult
{
private:
  uint32_t upperLimit;

public:
  IntMult(uint32_t upperLimit):
    upperLimit(upperLimit)
  {}
  // Int multiply
  template<typename Rng>
  uint32_t operator()(Rng& rng) 
  {
    uint32_t x = rng();
    uint64_t m = uint64_t(x) * uint64_t(upperLimit);
    return m >> 32;
  }

};

template<typename Func, typename Rng>
void timeIt(Func&& func, Rng&& rng)
{
  auto t1 = std::chrono::high_resolution_clock::now();
  for(int i = 0; i < 1000000; ++i)
  {
    func(rng);
  }
  auto t2 = std::chrono::high_resolution_clock::now();

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;

  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << ms_double.count() << "ms\n";
}

template<typename Func, typename Rng>
auto getVals(Func&& func, Rng&& rng)
{
  constexpr auto numvals{1000000};
  std::array<std::uint32_t, numvals> vals;
  for(int i = 0; i < numvals; ++i)
  {
    vals[i] = func(rng);
  }
  return vals;
}

int main()
{
  std::random_device rd;
  std::array<int, std::mt19937_64::state_size> seed_data {};
  std::generate(std::begin(seed_data), std::end(seed_data),
      std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  auto rng = std::mt19937_64{ seq };

  constexpr auto limit = 100;
  std::uniform_int_distribution<> intDistNumParams{0, limit-1};
  IntMult intMultDist(limit);
  Xoshiro256ss rng2;
  for(int i = 0; i < 10000; ++i)
  {
    rng2();
  }
  jsf32 rng3;

  timeIt(intMultDist, rng);
  timeIt(intMultDist, rng2);
  timeIt(intMultDist, rng3);
  timeIt(intDistNumParams, rng);
  timeIt(intDistNumParams, rng2);
  timeIt(intDistNumParams, rng3);


  /* auto countThem = [](const auto& multVals) */
  /* { */
  /*   for (int i = 0; i < limit + 1; ++i) */
  /*   { */
  /*     std::cerr << "Num " << i << ": " << std::count_if(multVals.begin(), multVals.end(), [i](auto input){ return input == i; }) << std::endl; */
  /*   } */
  /* }; */
  /* auto vals = getVals(intMultDist, rng2); */
  /* countThem(vals); */

  /* auto stdVals = getVals(intDistNumParams, rng2); */
  /* countThem(stdVals); */

}
