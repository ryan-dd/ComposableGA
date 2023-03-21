#ifndef EVVY_CONSTANT_PROBABILITY_H
#define EVVY_CONSTANT_PROBABILITY_H

namespace evvy
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
