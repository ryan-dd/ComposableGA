#ifndef EVY_STD_PROBABILITY_RNG
#define EVY_STD_PROBABILITY_RNG

#include <random>
#include <ranges>

namespace evy
{

class StdProbabilityRng
{
private:
  std::mt19937_64 rng{};
  std::uniform_real_distribution<double> dist;
public:
  StdProbabilityRng():
    rng{ [](){
      std::random_device rd;
      std::array<int, std::mt19937_64::state_size> seedData{};
      std::ranges::generate(seedData, std::ref(rd));
      std::seed_seq seedSeq(std::begin(seedData), std::end(seedData));
      return std::mt19937_64{ seedSeq };
    }() },
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
