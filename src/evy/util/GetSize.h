#ifndef EVY_GET_SIZE_H
#define EVY_GET_SIZE_H

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
}

template<typename ChromosomeType>
std::size_t getSize(ChromosomeType& chromosome)
{
  if constexpr(std::is_aggregate_v<ChromosomeType>)
  {
    return boost::pfr::tuple_size_v<ChromosomeType>;
  }
  else if constexpr(TupleLike<ChromosomeType>)
  {
    return std::tuple_size_v<ChromosomeType>;
  }
  else if constexpr( requires (ChromosomeType chromosome){ chromosome.size(); } )
  {
    return chromosome.size();
  }
  else if constexpr( requires { ChromosomeType::size(); } )
  {
    return ChromosomeType::size();
  }
}


}

#endif
