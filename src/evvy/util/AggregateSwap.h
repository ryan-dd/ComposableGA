#ifndef EVVY_AGGREGATE_SWAP_H
#define EVVY_AGGREGATE_SWAP_H

#include <tuple>
#include <utility>
#include <type_traits>
#include <stdexcept>
#include <cassert>

#include <boost/pfr.hpp>

namespace evvy
{

namespace detail
{

template<typename Aggregate, typename Indices = std::make_index_sequence<boost::pfr::tuple_size<Aggregate>::value>>
struct RuntimeSwapFuncTable;

template<typename Aggregate, std::size_t Index>
void aggregateMemberSwap(Aggregate& t1, Aggregate& t2) noexcept
{
  using std::swap;
  swap(boost::pfr::get<Index>(t1), boost::pfr::get<Index>(t2));
}

template<typename Aggregate, std::size_t... Indices>
struct RuntimeSwapFuncTable<Aggregate, std::index_sequence<Indices...>>
{
  using get_func_ptr = void (*)(Aggregate&, Aggregate&) noexcept;
  static constexpr get_func_ptr table[] = { &aggregateMemberSwap<Aggregate, Indices>... };
};

template<typename Aggregate, std::size_t... Indices>
constexpr typename RuntimeSwapFuncTable<Aggregate, std::index_sequence<Indices...>>::get_func_ptr
RuntimeSwapFuncTable<Aggregate, std::index_sequence<Indices...>>::table[];

}

template<typename Aggregate>
constexpr void aggregateMemberSwap(Aggregate& t1, Aggregate& t2, std::size_t index)
{
  using aggregate_type = typename std::remove_reference<Aggregate>::type;
  detail::RuntimeSwapFuncTable<aggregate_type>::table[index](t1, t2);
}

}

#endif
