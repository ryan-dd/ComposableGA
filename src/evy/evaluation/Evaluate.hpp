#ifndef EVY_EVALUATE_HPP
#define EVY_EVALUATE_HPP

#include <ranges>
#include <concepts>
#include <algorithm>

namespace evy
{

template<std::ranges::range ScoreContainer, typename ObjFunction>
class Evaluate
{
private:
  std::reference_wrapper<ScoreContainer> scores;
  ObjFunction objFunction;
public:
  constexpr Evaluate(ScoreContainer& scores, ObjFunction objFunction): 
    scores(scores),
    objFunction(std::move(objFunction))
  {}

  template<std::ranges::input_range ChromosomeContainer>
  requires std::convertible_to<
            std::invoke_result_t<ObjFunction, std::ranges::range_value_t<ChromosomeContainer>&>, 
            std::ranges::range_value_t<ScoreContainer>>
  constexpr void operator()(const ChromosomeContainer& container)
  {
    std::ranges::transform(
        container, 
        std::ranges::begin(scores.get()), 
        objFunction);
  }

};

}

#endif
