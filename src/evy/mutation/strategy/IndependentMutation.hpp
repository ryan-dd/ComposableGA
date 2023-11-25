#ifndef EVY_INDEPENDENT_MUTATION_H
#define EVY_INDEPENDENT_MUTATION_H

#include "evy/rng/StdProbabilityRng.hpp"
#include "evy/util/concepts/TupleLike.hpp"
#include "evy/util/ConditionallyApplyFunctions.hpp"

#include <type_traits>
#include <concepts>

namespace evy
{

template<
  std::invocable MutationProbability,
  TupleLike MutateFunctions,
  std::invocable ProbabilityGenerator = StdProbabilityRng
> 
class IndependentMutation
{
public:
  explicit IndependentMutation(
      MutateFunctions mutateFunctions, 
      MutationProbability mutationProbability,
      ProbabilityGenerator generator = StdProbabilityRng{})
    : mutateFunctions(mutateFunctions),
      mutationProbability(mutationProbability),
      generator(generator)
  {
  }

  template<typename ChromosomeType>
  requires TupleLike<ChromosomeType> || std::is_aggregate_v<ChromosomeType>
  void operator()(ChromosomeType& chromosome)
  {
    auto shouldMutate = [this](){ return generator() < mutationProbability(); };
    conditionallyApplyFunctions(chromosome, mutateFunctions, shouldMutate);
  }

private:
  MutateFunctions mutateFunctions;
  MutationProbability mutationProbability;
  ProbabilityGenerator generator;
};

}

#endif
