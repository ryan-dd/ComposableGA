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
      const int& get_num_parameters();
      const std::vector<std::vector<float> >& get_constraints();

    private:
      int mNumParameters;
      std::vector<std::vector<float> > mConstraints;
  };

  inline const std::string NUM_PARAMS_GREATER_ZERO_ERROR_MSG = "Number of parameters must be greater than 0";
  inline const std::string CONSTRAINT_PARAMETER_MATCH_ERROR_MSG = "Constraints do not equal parameters";
  inline const std::string CONSTRAINT_SIZE_ERROR_MSG = "Constraints must have 2 values: lower bounds and upper bounds";
}
#endif
