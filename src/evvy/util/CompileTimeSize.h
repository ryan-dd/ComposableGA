#ifndef EVVY_COMPILE_TIME_SIZE_H
#define EVVY_COMPILE_TIME_SIZE_H

namespace evvy
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
}

}

#endif
