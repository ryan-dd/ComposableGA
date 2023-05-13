#ifndef EVY_EVALUATE_H
#define EVY_EVALUATE_H

#include <ranges>
#include <concepts>
#include <algorithm>

namespace evy
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
    objFunction(std::move(objFunction))
  {}

  template<std::ranges::input_range ChromosomeContainer>
  requires std::convertible_to<
            std::invoke_result_t<ObjFunction, std::ranges::range_value_t<ChromosomeContainer>&>, 
            std::ranges::range_value_t<ScoreContainer>>
  void operator()(const ChromosomeContainer& container)
  {
    std::ranges::transform(
        container, 
        std::ranges::begin(scores), 
        objFunction);
  }

};

}

#endif
