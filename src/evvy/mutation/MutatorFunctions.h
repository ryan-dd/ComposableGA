#ifndef EVVY_MUTATOR_FUNCTIONS_H
#define EVVY_MUTATOR_FUNCTIONS_H

#include "../util/concepts/TupleLike.h"
#include "../util/concepts/ValueMatching.h"
#include "../util/concepts/IntType.h"

#include <random>
#include <type_traits>
#include <boost/pfr.hpp>

namespace
{
  template<typename ValueType>
  requires (evvy::IntType<ValueType> || std::is_floating_point_v<ValueType>)
  auto getGenerator(ValueType min, ValueType max)
  {
    if constexpr(std::is_floating_point_v<ValueType>)
    {
      return std::uniform_real_distribution(min, max);
    }
    else if constexpr(evvy::IntType<ValueType>)
    {
      return std::uniform_int_distribution(min, max);
    }
  }
}

namespace evvy
{

template<std::size_t Index, typename ValueType> 
requires (evvy::IntType<ValueType> || std::is_floating_point_v<ValueType>)
class MutateNumeric
{
public:
  MutateNumeric(ValueType min, ValueType max):
    min{min},
    max{max},
    generator{getGenerator(min, max)},
    rng(std::random_device{}())
  {

  }

  template<typename ChromosomeType>
  requires 
    TupleWithMemberTypeAtIndex<ChromosomeType, ValueType, Index> || 
    IndexableWithValue<ChromosomeType, ValueType> ||
    AggregateWithMemberTypeAtIndex<ChromosomeType, ValueType, Index>
  void operator()(ChromosomeType& chromosome)
  {
    if constexpr(AggregateWithMemberTypeAtIndex<ChromosomeType, ValueType, Index>)
    {
      boost::pfr::get<Index>(chromosome) = generator(rng);
    }
    else if constexpr(TupleWithMemberTypeAtIndex<ChromosomeType, ValueType, Index>)
    {
      using std::get;
      get<Index>(chromosome) = generator(rng);
    }
    else if constexpr( IndexableWithValue<ChromosomeType, ValueType> )
    {
      chromosome[Index] = generator(rng);
    }
  }

private:
  ValueType min;
  ValueType max;
  std::mt19937 rng;
  decltype(std::function{getGenerator<ValueType>})::result_type generator;
};

}

#endif
