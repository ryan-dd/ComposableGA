#ifndef EVVY_INT_TYPE_H
#define EVVY_INT_TYPE_H

namespace evvy 
{

template<typename T>
concept IntType = requires
{
  std::is_same_v<T, short> ||
  std::is_same_v<T, int> ||
  std::is_same_v<T, long> ||
  std::is_same_v<T, long long> ||
  std::is_same_v<T, unsigned short> ||
  std::is_same_v<T, unsigned int> ||
  std::is_same_v<T, unsigned long> ||
  std::is_same_v<T, unsigned long long>;
};

}

#endif
