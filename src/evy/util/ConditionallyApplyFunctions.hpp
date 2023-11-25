#ifndef CONDITIONALLY_APPLY_FUNCTIONS_HPP
#define CONDITIONALLY_APPLY_FUNCTIONS_HPP

#include "boost/pfr/tuple_size.hpp"
#include "boost/pfr/core.hpp"

namespace evy
{

namespace detail
{

template<std::size_t index, typename InputType>
requires TupleLike<InputType> || std::is_aggregate_v<InputType>
constexpr void conditionallyApplyFunction(InputType& input, TupleLike auto& tupleOfFunctions, std::invocable auto& condition)
{
    if(!condition())
    {
        return;
    }

    if constexpr (TupleLike<InputType>)
    {
        using std::get;
        get<index>(tupleOfFunctions)(get<index>(input));
    }
    else if constexpr(std::is_aggregate_v<InputType>)
    {
        using std::get;
        get<index>(tupleOfFunctions)(boost::pfr::get<index>(input));
    }  
}


template <typename InputType, std::size_t... Idx>
constexpr void conditionallyApplyFunctions(InputType& input, TupleLike auto& tupleOfFunctions, std::invocable auto& condition, std::index_sequence<Idx...>) {
    (conditionallyApplyFunction<Idx>(input, tupleOfFunctions, condition), ...);
}

}

template <typename InputType, TupleLike TupleOfFunctions>
requires (TupleLike<InputType> || std::is_aggregate_v<InputType>)
// TODO validate TupleOfFunctions function type at each tuple index can operate on input type at same index
constexpr void conditionallyApplyFunctions(InputType& input, TupleOfFunctions& tupleOfFunctions, std::invocable auto& condition) {
    
    if constexpr (TupleLike<InputType>)
    {
        static_assert(
            std::tuple_size_v<InputType> == std::tuple_size_v<TupleOfFunctions>,
            "There must be enough functions for each tuple arg of the input");
        detail::conditionallyApplyFunctions(input, tupleOfFunctions, condition, std::make_index_sequence< std::tuple_size_v<InputType> >{});
    }
    else if constexpr (std::is_aggregate_v<InputType>)
    {
        static_assert(
            boost::pfr::tuple_size_v<InputType> == std::tuple_size_v<TupleOfFunctions>,
            "There must be enough functions for each member of the input");
        detail::conditionallyApplyFunctions(input, tupleOfFunctions, condition, std::make_index_sequence< boost::pfr::tuple_size_v<InputType> >{});
    }
}

}

#endif
