#ifndef OPTIMIZATIONPROBLEM_H
#define OPTIMIZATIONPROBLEM_H

#include <vector>

namespace EvoAlgos
{
  class OptimizationProblem
  {
    public:
      OptimizationProblem(int number_of_parameters, std::vector<std::vector<float> > constraints);
      virtual ~OptimizationProblem();
      float objective_function(std::vector<float>);

    private:
      int mNumParameters;
      std::vector<std::vector<float> > mConstraints;
  };
}
#endif
