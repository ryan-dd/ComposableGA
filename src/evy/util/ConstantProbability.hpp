#ifndef EVY_CONSTANT_PROBABILITY_HPP
#define EVY_CONSTANT_PROBABILITY_HPP

namespace evy
{

template<typename ValueType>
class ConstantProbability
{
public:
  constexpr explicit ConstantProbability(ValueType threshold):
    threshold{threshold}
  {
  }

  constexpr ValueType operator()() const
  {
    return threshold;
  }

private: 
  ValueType threshold;
};

}

#endif
