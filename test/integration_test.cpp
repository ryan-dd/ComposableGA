#include <iostream>

#include <gtest/gtest.h>

#include "OptimizationProblem.hpp"
#include "GeneticAlgorithm.hpp"


TEST(Integration, TestRosenbrockWithGeneticAlgo) {
    int number_of_parameters = 2;
    std::vector<std::vector<double> > constraints{{-10, 10}, {-10, 10}};
    EvoAlgos::OptimizationProblem opti_problem = EvoAlgos::OptimizationProblem(number_of_parameters, constraints);
    EvoAlgos::GeneticAlgorithm algo = EvoAlgos::GeneticAlgorithm(4096, 1000, 5, 0.8, 0.4);
    std::vector<double> answer = algo.run(opti_problem);
    std::cout << answer[0] << " " << answer[1] << " " << opti_problem.objective_function(answer) << '\n';
}
