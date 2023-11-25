#ifndef EVY_CONSTANT_PROBABILITY_HPP
#define EVY_CONSTANT_PROBABILITY_HPP

namespace evy
{

template<typename ValueType>
class ConstantProbability
{
public:
  ConstantProbability(ValueType threshold):
    threshold{threshold}
  {
  }

  ValueType operator()()
  {
    return threshold;
  }

private: 
  ValueType threshold;
};

}

#endif
