#ifndef EVVY_CROSSOVER_H
#define EVVY_CROSSOVER_H

#include "../rng/StdProbabilityRng.h"

#include <ranges>

namespace evvy
{

template<
  std::invocable CrossoverProbability,
  typename CrossoverStrategy,
  std::invocable ProbabilityGenerator = StdProbabilityRng
>
class Crossover
{
public:
  Crossover(
      CrossoverProbability crossoverProbability, 
      CrossoverStrategy crossoverStrategy,
      ProbabilityGenerator generator = StdProbabilityRng{}
    ):
    crossoverProbability{std::move(crossoverProbability)},
    doCrossover{std::move(crossoverStrategy)},
    generator{std::move(generator)}
  {
  }

  template<std::ranges::range ChromosomeContainer>
  requires std::invocable<CrossoverStrategy, 
           std::ranges::range_value_t<ChromosomeContainer>&, 
           std::ranges::range_value_t<ChromosomeContainer>&> // Matches signature of doCrossover(...)
  void operator()(ChromosomeContainer& chromosomes)
  {
    for(auto it1 = chromosomes.begin(); it1 != chromosomes.end(); std::advance(it1, 2))
    {
      auto it2{++it1};
      if(it2 == chromosomes.end())
      {
        return;
      }

      if (generator() < crossoverProbability())
      {
        doCrossover(*it1, *it2);
      }
    }
  }

private:
  CrossoverProbability crossoverProbability;
  CrossoverStrategy doCrossover;
  ProbabilityGenerator generator;
};

} // namespace evvy

#endif
