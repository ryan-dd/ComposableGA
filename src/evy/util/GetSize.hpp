#ifndef EVY_GET_SIZE_HPP
#define EVY_GET_SIZE_HPP

namespace evy
{

template<typename T>
requires std::is_aggregate_v<T> || TupleLike<T>
constexpr std::size_t compileTimeSize()
{
  if constexpr(std::is_aggregate_v<T>)
  {
    return boost::pfr::tuple_size_v<T>;
  }
  else if constexpr(TupleLike<T>)
  {
    return std::tuple_size_v<T>;
  }
  else
  {
    static_assert(false, "Must be aggregate or tupleLike in function");
  }
}

}

#endif
