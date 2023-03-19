#ifndef EVVY_EVALUATE_H
#define EVVY_EVALUATE_H

#include <algorithm>
#include <ranges>

namespace evvy
{

template<typename ScoreContainer, typename ObjFunction>
class Evaluate
{
private:
  ScoreContainer& scores;
  ObjFunction objFunction;
public:
  Evaluate(ScoreContainer& scores, ObjFunction objFunction): 
    scores(scores),
    objFunction(objFunction)
  {}

  template<std::ranges::input_range ChromosomeContainer>
  void operator()(ChromosomeContainer& container)
  {
    std::ranges::transform(container, scores.begin(), objFunction);
  }

};

}

#endif
