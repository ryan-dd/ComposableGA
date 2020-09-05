#include <math.h>
#include "OptimizationProblem.hpp"

float EvoAlgos::OptimizationProblem::objective_function(std::vector<float> inputs)
{
  // rosenbrock function
  float x = inputs[0];
  float y = inputs[1];
  int a = 1;
  int b = 100;
  return pow((a-x), 2) + b*pow((y-pow(x, 2)), 2);
}

EvoAlgos::OptimizationProblem::OptimizationProblem(int number_of_parameters, std::vector<std::vector<float> > constraints):
  mNumParameters(number_of_parameters),
  mConstraints(constraints){}

EvoAlgos::OptimizationProblem::~OptimizationProblem()
{}
