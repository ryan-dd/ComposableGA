#ifndef EVY_PIPELINE_H
#define EVY_PIPELINE_H

#include <concepts>
#include <algorithm>
#include <functional>
#include <initializer_list>

namespace evy
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
      ChromosomeContainer&& chromosomes, 
      StopCondition&& shouldStop, 
      PipelineFunctions&&... functions)
  {
    while(true)
    {
      // Invokes each function in left to right order
      (std::forward<PipelineFunctions>(functions)(chromosomes), ...);

      if(shouldStop())
      {
        break;
      }
    }
  }
};

}
#endif
