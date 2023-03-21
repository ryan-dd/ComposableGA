#ifndef EVVY_VALUE_MATCHING_H
#define EVVY_VALUE_MATCHING_H

#include <boost/pfr/core.hpp>

namespace evvy
{

template<typename T, typename ValueType>
concept IndexableWithValue = requires(T container)
{
  {container[0]} -> std::convertible_to<ValueType>;
};

template<typename Aggregate, typename ValueType, std::size_t Index>
concept AggregateWithMemberTypeAtIndex = requires (Aggregate a)
{
  std::is_aggregate_v<Aggregate>;
  {boost::pfr::get<Index>(a)} -> std::convertible_to<ValueType>;
};

template<typename Tuple, typename ValueType, std::size_t Index>
concept TupleWithMemberTypeAtIndex = requires (Tuple a)
{
  requires evvy::TupleLike<Tuple>;
  {std::get<Index>(a)} -> std::convertible_to<ValueType>;
};

}

#endif
