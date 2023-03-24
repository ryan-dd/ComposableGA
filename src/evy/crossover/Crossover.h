#ifndef EVY_CROSSOVER_H
#define EVY_CROSSOVER_H

#include "../rng/StdProbabilityRng.h"

#include <ranges>

namespace evy
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
    for(auto it1 = std::ranges::begin(chromosomes); 
        it1 != std::ranges::end(chromosomes); 
        std::ranges::advance(it1, 2))
    {
      auto it2{++it1};
      if(it2 == std::ranges::end(chromosomes))
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

} // namespace evy

#endif
