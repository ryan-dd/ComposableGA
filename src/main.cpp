#include <iostream>
#include <vector>
#include "OptimizationProblem.hpp"

int main (int argc, char *argv[])
{
  try
  { 
    int number_of_parameters = 2;
    std::vector<std::vector<float> > constraints{{-10, 10}, {-10, 10}};
    EvoAlgos::OptimizationProblem problem = EvoAlgos::OptimizationProblem(number_of_parameters, constraints);
    float example_result = problem.objective_function(std::vector<float>{-1, 3});
    std::cout << "Result is: " << example_result << '\n';
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
}
