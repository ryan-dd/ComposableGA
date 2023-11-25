#ifndef EVY_INDEPENDENT_MUTATION_HPP
#define EVY_INDEPENDENT_MUTATION_HPP

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
  MutateFunctions mutateFunctions;
  MutationProbability mutationProbability;
  ProbabilityGenerator generator = ProbabilityGenerator{};

  template<typename ChromosomeType>
  requires TupleLike<ChromosomeType> || std::is_aggregate_v<ChromosomeType>
  constexpr void operator()(ChromosomeType& chromosome)
  {
    auto shouldMutate = [this](){ return generator() < mutationProbability(); };
    conditionallyApplyFunctions(chromosome, mutateFunctions, shouldMutate);
  }

};

}

#endif
