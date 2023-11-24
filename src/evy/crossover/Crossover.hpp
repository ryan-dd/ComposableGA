#ifndef EVY_CROSSOVER_H
#define EVY_CROSSOVER_H

#include "../rng/StdProbabilityRng.hpp"

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
    for(const auto& chromosomePair : chromosomes | std::views::chunk(2))
    {
      // If "chromosomes" are passed in with an odd size, we can't do crossover on the last element 
      // Since it has no matching pair
      if(chromosomePair.size() != 2) 
      {
        continue;
      }

      if (generator() < crossoverProbability())
      {
        doCrossover(chromosomePair[0], chromosomePair[1]);
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
