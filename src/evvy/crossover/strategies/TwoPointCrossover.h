#ifndef EVVY_TWO_POINT_CROSSOVER_H
#define EVVY_TWO_POINT_CROSSOVER_H

#include "../../util/CompileTimeSize.h"
#include "../../util/AggregateSwap.h"
#include "../../rng/FastIndexRng.h"

namespace evvy
{

template<
  typename ChromosomeType,
  std::invocable<ChromosomeType&, ChromosomeType&, std::size_t> SwapFunction,
  typename IndexRng = FastIndexRng
>
class TwoPointCrossover
{
public:
  TwoPointCrossover(
      SwapFunction&& swapFunction,
      IndexRng&& indexRng = FastIndexRng(compileTimeSize<ChromosomeType>())
    ):
    doSwap(swapFunction),
    indexRng(indexRng)
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
  SwapFunction& doSwap;
  IndexRng& indexRng;
};

namespace detail
{
  template<typename ChromosomeType>
  using TwoPointCrossoverWithAggregate = TwoPointCrossover<ChromosomeType, decltype(evvy::aggregateMemberSwap<ChromosomeType>)>;
}

template<typename ChromosomeType>
class TwoPointCrossoverWithAggregate: public detail::TwoPointCrossoverWithAggregate<ChromosomeType>
{
public:
  TwoPointCrossoverWithAggregate():
    detail::TwoPointCrossoverWithAggregate<ChromosomeType>(aggregateMemberSwap<ChromosomeType>)
  {
  }
};

}

#endif
