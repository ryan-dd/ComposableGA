#ifndef EVY_VALUE_MATCHING_HPP
#define EVY_VALUE_MATCHING_HPP

#include <boost/pfr/core.hpp>

namespace evy
{

template<typename T, typename ValueType>
concept IndexableWithValue = requires(T container)
{
  { container[0] } -> std::convertible_to<ValueType>;
};

template<typename Aggregate, typename ValueType, std::size_t Index>
concept AggregateWithMemberTypeAtIndex = requires (Aggregate a)
{
  requires std::is_aggregate_v<Aggregate>;
  { boost::pfr::get<Index>(a) } -> std::convertible_to<ValueType>;
};

template<typename Tuple, typename ValueType, std::size_t Index>
concept TupleWithMemberTypeAtIndex = requires (Tuple tuple)
{
  requires evy::TupleLike<Tuple>;
  { get<Index>(tuple) } -> std::convertible_to<ValueType>;
};

}

#endif
