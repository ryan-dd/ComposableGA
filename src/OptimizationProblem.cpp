#include <exception>
#include <math.h>
#include <string>

#include "OptimizationProblem.hpp"

double EvoAlgos::OptimizationProblem::objective_function(std::vector<double>& inputs)
{
  // Rosenbrock function
  double x = inputs[0];
  double y = inputs[1];
  return pow((a-x), 2) + b*pow((y-pow(x, 2)), 2);
}

int EvoAlgos::OptimizationProblem::get_num_parameters()
{
  return mNumParameters;
}
      
std::vector<std::vector<double> >& EvoAlgos::OptimizationProblem::get_constraints()
{
  return mConstraints;
}

const std::string EvoAlgos::OptimizationProblem::NUM_PARAMS_GREATER_ZERO_ERROR_MSG = "Number of parameters must be greater than 0";
const std::string EvoAlgos::OptimizationProblem::CONSTRAINT_PARAMETER_MATCH_ERROR_MSG = "Constraints do not equal parameters";
const std::string EvoAlgos::OptimizationProblem::CONSTRAINT_SIZE_ERROR_MSG = "Constraints must have 2 values: lower bounds and upper bounds";

EvoAlgos::OptimizationProblem::OptimizationProblem(int number_of_parameters, std::vector<std::vector<double> > constraints):
  mNumParameters(number_of_parameters),
  mConstraints(constraints)
{
  if (number_of_parameters < 1) 
  {
    throw std::runtime_error(NUM_PARAMS_GREATER_ZERO_ERROR_MSG);
  }
  if (constraints.size() != mNumParameters)
  {
    throw std::runtime_error(CONSTRAINT_PARAMETER_MATCH_ERROR_MSG); 
  }
  for (auto const& row : constraints)
  {
    if (row.size() != 2)
    {
      throw std::runtime_error(CONSTRAINT_SIZE_ERROR_MSG); 
    }
  }
  a = 1;
  b = 100;
  
}

EvoAlgos::OptimizationProblem::~OptimizationProblem()
{}
