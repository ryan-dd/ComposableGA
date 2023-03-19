#ifndef EVVY_INDEPENDENT_CROSSOVER_H
#define EVVY_INDEPENDENT_CROSSOVER_H

#include "../util/AggregateSwap.h"
#include "../rng/xoshiro256ss.h"
#include "../rng/IntMult.h"

#include <boost/pfr.hpp>

#include <random>
#include <cassert>
#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <functional>
#include <ranges>

namespace evvy
{

template<
  typename ChromosomeType,
  size_t chromosomeSize = boost::pfr::tuple_size_v<ChromosomeType>,
  std::invocable<ChromosomeType&, ChromosomeType&, std::size_t> SwapFunc = decltype(aggregateMemberSwap<ChromosomeType>),
  std::invocable IndexRng = Xoshiro256ss,
  std::invocable<IndexRng&> IndexDist = IntMult,
  std::invocable CrossoverProbabilityRng = Xoshiro256ss,
  std::invocable<CrossoverProbabilityRng&> CrossoverProbabilityDist = std::uniform_real_distribution<double>
>
class CrossoverIndependentParameters
{
public:
  explicit CrossoverIndependentParameters(
      double crossoverProbability, 
      SwapFunc& swapFunc = aggregateMemberSwap<ChromosomeType>,
      IndexDist&& indexDist = IntMult(chromosomeSize),
      IndexRng&& indexRng = Xoshiro256ss{},
      CrossoverProbabilityDist&& probabilityDist = std::uniform_real_distribution{},
      CrossoverProbabilityRng&& probabilityRng = Xoshiro256ss{}):
    crossoverProbability(crossoverProbability),
    swapFunc(swapFunc),
    indexDist(indexDist),
    indexRng(indexRng),
    probabilityDist(probabilityDist),
    probabilityRng(probabilityRng)
  {
    if(crossoverProbability < 0 || crossoverProbability > 1)
    {
      throw std::invalid_argument("Double must be greater than or equal to 0 and less than 1");
    }
  }

  template<std::ranges::output_range<ChromosomeType> ChromosomeContainer>
  void operator()(ChromosomeContainer& chromosomes)
  {
    for(auto it1 = chromosomes.begin(); it1 != chromosomes.end(); std::advance(it1, 2))
    {
      auto it2{++it1};
      if(it2 == chromosomes.end())
      {
        return;
      }

      const auto probability{probabilityDist(probabilityRng)};

      if (probability > crossoverProbability)
      {
        continue;
      }

      auto& first{*it1};
      auto& second{*it2};
      const auto crossover_index1{indexDist(indexRng)};
      const auto crossover_index2{indexDist(indexRng)};
      const auto beginIndex{std::min(crossover_index1, crossover_index2)};
      const auto endIndex{std::max(crossover_index1, crossover_index2) + 1};

      for(auto chromosomeIndex{beginIndex}; chromosomeIndex < endIndex; ++chromosomeIndex)
      {
        swapFunc(first, second, chromosomeIndex);
      }
    }
  }

private:
  double crossoverProbability{};
  SwapFunc& swapFunc;
  IndexDist& indexDist;
  IndexRng& indexRng;
  CrossoverProbabilityDist& probabilityDist;
  CrossoverProbabilityRng& probabilityRng;
};

} // namespace evvy

#endif
