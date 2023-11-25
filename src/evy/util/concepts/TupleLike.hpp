#ifndef EVY_TUPLE_LIKE_H
#define EVY_TUPLE_LIKE_H

#include <type_traits>

namespace evy
{

namespace detail
{

template<class T, std::size_t N>
concept TupleElementAtIndex =
  requires(T t) 
  {
    // tuple_element_t is defined for N
    typename std::tuple_element_t<N, T>;

    // get<N>(t) returns a reference that is the same type as tuple_element_t
    // Allow ADL for get
    { get<N>(t) } -> std::same_as<std::tuple_element_t<N, T>&>;
  };

template<class T>
concept TupleLike =
  requires(T t) 
  {
    // tuple_size::type is defined
    typename std::tuple_size<T>::type; 
    // tuple_size_v returns std::size_t
    { std::tuple_size_v<T> } -> std::convertible_to<std::size_t>;

    // tuple_size inherits from integral_constant<std::size_t, N>
    requires std::derived_from<
      std::tuple_size<T>, 
      std::integral_constant<std::size_t, std::tuple_size_v<T>>
    >;
  } && 
  // checks each tuple element has required functionality
  []<std::size_t... N>(std::index_sequence<N...>) 
  { 
    return (detail::TupleElementAtIndex<T, N> && ...); 
  }(std::make_index_sequence<std::tuple_size_v<T>>());

}

template<class T>
concept TupleLike = detail::TupleLike<std::remove_cvref_t<T>>;

}


#endif
