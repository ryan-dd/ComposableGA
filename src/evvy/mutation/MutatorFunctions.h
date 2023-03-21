#ifndef EVVY_MUTATOR_FUNCTIONS_H
#define EVVY_MUTATOR_FUNCTIONS_H

#include "../util/TupleLike.h"
#include "../rng/prng/xoshiro256ss.h"

#include <random>
#include <ratio>
#include <type_traits>
#include <boost/pfr.hpp>

template<typename T>
concept IntType = requires
{
  std::is_same_v<T, short> ||
  std::is_same_v<T, int> ||
  std::is_same_v<T, long> ||
  std::is_same_v<T, long long> ||
  std::is_same_v<T, unsigned short> ||
  std::is_same_v<T, unsigned int> ||
  std::is_same_v<T, unsigned long> ||
  std::is_same_v<T, unsigned long long>;
};

template<typename T>
concept Indexable = requires(T container)
{
  container[0];
};

template<typename Aggregate, typename ValueType, std::size_t Index>
concept AggregateWithMemberTypeAtIndex = requires (Aggregate a)
{
  std::is_aggregate_v<Aggregate>;
  {boost::pfr::get<Index>(a)} -> std::convertible_to<ValueType>;
};

namespace
{
  template<typename ValueType>
  auto getGenerator(ValueType min, ValueType max)
  {
    if constexpr(std::is_floating_point_v<ValueType>)
    {
      return std::uniform_real_distribution(min, max);
    }
    else if constexpr(IntType<ValueType>)
    {
      return std::uniform_int_distribution(min, max);
    }
    else
    {
      static_assert(!sizeof(ValueType), "ValueType must be IntType or floating_point type");
    }
  }
}

namespace evvy
{

template<std::size_t Index, typename ChromosomeType, typename ValueType, ValueType min, ValueType max> 
requires (IntType<ValueType> || std::is_floating_point_v<ValueType>) &&
( TupleLike<ChromosomeType> || Indexable<ChromosomeType> || AggregateWithMemberTypeAtIndex<ChromosomeType, ValueType, Index>)
void mutateNumeric(ChromosomeType& chromosome)
{
  static std::mt19937 rng(std::random_device{}());
  static std::uniform_real_distribution<> generator(min, max);

  if constexpr(std::is_aggregate_v<ChromosomeType>)
  {
    boost::pfr::get<Index>(chromosome) = generator(rng);
  }
  else if constexpr(TupleLike<ChromosomeType>)
  {
    using std::get;
    get<Index>(chromosome) = generator(rng);
  }
  else if constexpr( Indexable<ChromosomeType> )
  {
    chromosome[Index] = generator(rng);
  }
  else
  {
    static_assert(!sizeof(ChromosomeType), "ChromosomeType must be an aggregate, tuple, or indexable");
  }
};

}

#endif
