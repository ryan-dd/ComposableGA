#ifndef EVVY_MUTATION_H
#define EVVY_MUTATION_H

#include "../rng/StdProbabilityRng.h"

#include <concepts>
#include <ranges>

namespace evvy
{

template<
  std::invocable MutationProbability,
  typename MutationStrategy,
  std::invocable ProbabilityGenerator = StdProbabilityRng
>
class Mutation
{
public:
  Mutation(
      MutationProbability mutationProbability,
      MutationStrategy mutationStrategy, 
      std::size_t chromosomeSize,
      ProbabilityGenerator generator = StdProbabilityRng{}
    ):
    mutationProbability(std::move(mutationProbability)),
    doMutation(std::move(mutationStrategy)),
    chromosomeSize(chromosomeSize),
    generator(std::move(generator))
  {
  }

  template<std::ranges::range ChromosomeContainer>
  requires std::invocable<MutationStrategy, 
           std::ranges::range_value_t<ChromosomeContainer>&, std::size_t>
  void operator()(ChromosomeContainer& chromosomes)
  {
    for(auto& chromosome: chromosomes)
    {
      for(auto index{0}; index < chromosomeSize; ++index)
      {
        if(generator() < mutationProbability())
        {
          doMutation(chromosome, index);
        }
      }
    }
  }

private:
  MutationProbability mutationProbability;
  MutationStrategy doMutation;
  std::size_t chromosomeSize;
  ProbabilityGenerator generator;
};

}

#endif
