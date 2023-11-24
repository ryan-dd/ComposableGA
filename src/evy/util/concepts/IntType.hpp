#ifndef EVY_INT_TYPE_H
#define EVY_INT_TYPE_H

#include <type_traits>
namespace evy 
{

template<typename T>
concept IntType = requires
{
  std::is_same_v<std::remove_cvref_t<T>, short> ||
  std::is_same_v<std::remove_cvref_t<T>, int> ||
  std::is_same_v<std::remove_cvref_t<T>, long> ||
  std::is_same_v<std::remove_cvref_t<T>, long long> ||
  std::is_same_v<std::remove_cvref_t<T>, unsigned short> ||
  std::is_same_v<std::remove_cvref_t<T>, unsigned int> ||
  std::is_same_v<std::remove_cvref_t<T>, unsigned long> ||
  std::is_same_v<std::remove_cvref_t<T>, unsigned long long>;
};

}

#endif
