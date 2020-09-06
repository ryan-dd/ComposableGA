#include <exception>
#include <math.h>
#include <string>

#include "OptimizationProblem.hpp"

float EvoAlgos::OptimizationProblem::objective_function(std::vector<float> inputs)
{
  // Rosenbrock function
  float x = inputs[0];
  float y = inputs[1];
  int a = 1;
  int b = 100;
  return pow((a-x), 2) + b*pow((y-pow(x, 2)), 2);
}

const int& EvoAlgos::OptimizationProblem::get_num_parameters()
{
  return mNumParameters;
}
      
const std::vector<std::vector<float> >& EvoAlgos::OptimizationProblem::get_constraints()
{
  return mConstraints;
}

EvoAlgos::OptimizationProblem::OptimizationProblem(int number_of_parameters, std::vector<std::vector<float> > constraints):
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
  
}

EvoAlgos::OptimizationProblem::~OptimizationProblem()
{}
