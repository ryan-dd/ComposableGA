#ifndef EVVY_EVALUATE_H
#define EVVY_EVALUATE_H

#include <ranges>
#include <concepts>

namespace evvy
{

template<std::ranges::range ScoreContainer, typename ObjFunction>
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
  requires std::convertible_to<
            std::invoke_result_t<ObjFunction, std::ranges::range_value_t<ChromosomeContainer>&>, 
            std::ranges::range_value_t<ScoreContainer>
           >
  void operator()(ChromosomeContainer& container)
  {
    std::ranges::transform(container, std::ranges::begin(scores), objFunction);
  }

};

}

#endif
