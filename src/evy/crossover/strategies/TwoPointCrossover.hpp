#ifndef EVY_TWO_POINT_CROSSOVER_HPP
#define EVY_TWO_POINT_CROSSOVER_HPP

#include "evy/util/GetSize.hpp"
#include "evy/util/AggregateSwap.hpp"
#include "evy/rng/FastIndexRng.hpp"

namespace evy
{

template<
  typename ChromosomeType,
  std::invocable<ChromosomeType&, ChromosomeType&, std::size_t> SwapStrategy = decltype(&aggregateMemberSwap<ChromosomeType>),
  typename IndexRng = FastIndexRng
>
class TwoPointCrossover
{
public:
  SwapStrategy swapStrategy{ &aggregateMemberSwap<ChromosomeType> };
  IndexRng indexRng{ FastIndexRng(compileTimeSize<ChromosomeType>()) };

  constexpr void operator()(ChromosomeType& first, ChromosomeType& second)
  {
    const auto crossover_index1{indexRng()};
    const auto crossover_index2{indexRng()};
    const auto beginIndex{std::min(crossover_index1, crossover_index2)};
    const auto endIndex{std::max(crossover_index1, crossover_index2)};

    for(auto chromosomeIndex{beginIndex}; chromosomeIndex < endIndex + 1; ++chromosomeIndex)
    {
      swapStrategy(first, second, chromosomeIndex);
    }
  }

};

}

#endif
