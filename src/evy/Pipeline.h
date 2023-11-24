#ifndef EVY_PIPELINE_H
#define EVY_PIPELINE_H

#include <concepts>

namespace evy
{

template<typename T>
concept StopCondition = requires(T func)
{
  {func()} -> std::convertible_to<bool>;
};

class Pipeline
{
public:
  template<
    typename ChromosomeContainer,
    std::invocable<ChromosomeContainer&>... PipelineFunctions
  >
  static void run(
      ChromosomeContainer&& chromosomes, 
      StopCondition auto&& shouldStop, 
      PipelineFunctions&&... functions)
  {
    while(true)
    {
      // Invokes each function in left to right order
      (std::forward<PipelineFunctions>(functions)(std::forward<ChromosomeContainer>(chromosomes)), ...);

      if(shouldStop())
      {
        break;
      }
    }
  }
};

}
#endif
