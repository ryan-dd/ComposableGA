#ifndef EVY_TWO_POINT_CROSSOVER_H
#define EVY_TWO_POINT_CROSSOVER_H

#include "../../util/GetSize.hpp"
#include "../../util/AggregateSwap.hpp"
#include "../../rng/FastIndexRng.hpp"

namespace evy
{

template<
  typename ChromosomeType,
  std::invocable<ChromosomeType&, ChromosomeType&, std::size_t> SwapFunction = decltype(&aggregateMemberSwap<ChromosomeType>),
  typename IndexRng = FastIndexRng
>
class TwoPointCrossover
{
public:
  TwoPointCrossover(
      SwapFunction swapFunction = &aggregateMemberSwap<ChromosomeType>,
      IndexRng indexRng = FastIndexRng(compileTimeSize<ChromosomeType>())
    ):
    doSwap(std::move(swapFunction)),
    indexRng(std::move(indexRng))
  {
  }

  void operator()(ChromosomeType& first, ChromosomeType& second)
  {
    const auto crossover_index1{indexRng()};
    const auto crossover_index2{indexRng()};
    const auto beginIndex{std::min(crossover_index1, crossover_index2)};
    const auto endIndex{std::max(crossover_index1, crossover_index2)};

    for(auto chromosomeIndex{beginIndex}; chromosomeIndex < endIndex + 1; ++chromosomeIndex)
    {
      doSwap(first, second, chromosomeIndex);
    }
  }

private:
  SwapFunction doSwap;
  IndexRng indexRng;
};

}

#endif
