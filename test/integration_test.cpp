#include <gtest/gtest.h>
#include "OptimizationProblem.hpp"
#include "GeneticAlgorithm.hpp"


TEST(Integration, TestRosenbrockWithGeneticAlgo) {
    int number_of_parameters = 2;
    std::vector<std::vector<double> > constraints{{-10, 10}, {-10, 10}};
    EvoAlgos::OptimizationProblem opti_problem = EvoAlgos::OptimizationProblem(number_of_parameters, constraints);
    EvoAlgos::GeneticAlgorithm algo = EvoAlgos::GeneticAlgorithm(1000, 2000);
    algo.run(opti_problem);
}
