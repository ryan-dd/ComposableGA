#ifndef OPTIMIZATIONPROBLEM_H
#define OPTIMIZATIONPROBLEM_H

#include <cstddef>
#include <vector>

namespace EvoAlgos
{
  class OptimizationProblem
  {
    public:
      OptimizationProblem(int number_of_parameters, std::vector<std::vector<double> > constraints);
      virtual ~OptimizationProblem();
      double objective_function(std::vector<double>);
      int get_num_parameters();
      std::vector<std::vector<double> >& get_constraints();
      
      static const std::string NUM_PARAMS_GREATER_ZERO_ERROR_MSG;
      static const std::string CONSTRAINT_PARAMETER_MATCH_ERROR_MSG;
      static const std::string CONSTRAINT_SIZE_ERROR_MSG;

    private:
      std::size_t mNumParameters;
      std::vector<std::vector<double> > mConstraints;
      int a;
      int b;
  };

}
#endif
