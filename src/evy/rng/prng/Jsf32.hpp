#ifndef JSF32_h
#define JSF32_h

#include <cstdint>

class jsf32
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;

  static inline uint32_t rot(uint32_t x, uint32_t k) noexcept { return (((x) << (k)) | ((x) >> (32 - (k)))); }
public:
  constexpr explicit jsf32(uint32_t seed = 0xdeadbeef) noexcept
  {
    a = 0xf1ea5eed;
    b = c = d = seed;
    for(size_t i = 0; i < 20; ++i)
      (*this)();
  }

  constexpr inline uint32_t operator()() noexcept
  {
    uint32_t e = a - rot(b, 27);
    a = b ^ rot(c, 17);
    b = c + d;
    c = d + e;
    d = e + a;
    return d;
  }

  using result_type = uint32_t;

  static constexpr result_type min()
  {
    return 0;
  }

  static constexpr result_type max()
  {
    return 0xFFFFFFFFu;
  }
};

#endif
