#ifndef EVY_STOP_AFTER_H
#define EVY_STOP_AFTER_H

namespace evy
{

class StopAfter
{
private:
  int currentIteration{0};
  int numIterations{0};

public:
  StopAfter(decltype(numIterations) numIterations): numIterations(numIterations) 
  {}

  bool operator()()
  {
    return currentIteration++ > numIterations;
  }
};

}

#endif
