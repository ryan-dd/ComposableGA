#ifndef EVVY_PIPELINE_H
#define EVVY_PIPELINE_H

#include <concepts>
#include <algorithm>
#include <functional>
#include <initializer_list>

namespace evvy
{

template<typename T>
concept stop_condition = requires(T func)
{
  {func()} -> std::convertible_to<bool>;
};

class Pipeline
{
public:
  template<
    typename ChromosomeContainer,
    stop_condition StopCondition,
    std::invocable<ChromosomeContainer&>... PipelineFunctions
  >
  static void run(
      ChromosomeContainer& chromosomes, 
      StopCondition&& shouldStop, 
      PipelineFunctions&&... functions)
  {
    while(true)
    {
      // Invokes each function in left to right order
      auto list = { (std::forward<PipelineFunctions>(functions)(chromosomes), 0)... };

      if(shouldStop())
      {
        break;
      }
    }
  }
};

}
#endif
