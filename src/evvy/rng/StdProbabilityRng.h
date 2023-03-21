#ifndef EVVY_STD_PROBABILITY_RNG
#define EVVY_STD_PROBABILITY_RNG

#include <random>

namespace evvy
{

class StdProbabilityRng
{
private:
  std::mt19937_64 rng{};
  std::uniform_real_distribution<double> dist;
public:
  StdProbabilityRng():
    rng{},
    dist(0.0, 1.0)
  {
  }

  decltype(dist(rng)) operator()()
  {
    return dist(rng);
  }
};

}

#endif
