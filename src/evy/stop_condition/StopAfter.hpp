#ifndef EVY_STOP_AFTER_HPP
#define EVY_STOP_AFTER_HPP

namespace evy
{

class StopAfter
{
private:
  int currentIteration{0};
  int numIterations{0};

public:
  constexpr explicit StopAfter(decltype(numIterations) numIterations): numIterations(numIterations) 
  {}

  constexpr bool operator()()
  {
    return ++currentIteration >= numIterations;
  }
};

}

#endif
