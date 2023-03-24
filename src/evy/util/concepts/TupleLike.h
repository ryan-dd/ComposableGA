#ifndef EVY_TUPLE_LIKE_H
#define EVY_TUPLE_LIKE_H

namespace evy
{

namespace detail
{
template<class T, std::size_t N>
concept tuple_element_at_index =
  requires(T t) 
  {
    typename std::tuple_element_t<N, std::remove_const_t<T>>;
    { get<N>(t) } -> std::convertible_to<const std::tuple_element_t<N, T>&>;
  };
}

template<class T>
concept TupleLike = !std::is_reference_v<T> && 
  requires(T t) 
  { 
    typename std::tuple_size<T>::type; 
    requires std::derived_from<
      std::tuple_size<T>, 
      std::integral_constant<std::size_t, std::tuple_size_v<T>>
    >;
  } && 
  []<std::size_t... N>(std::index_sequence<N...>) 
  { 
    return (detail::tuple_element_at_index<T, N> && ...); 
  }(std::make_index_sequence<std::tuple_size_v<T>>());
}

#endif
