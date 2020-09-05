#include <gtest/gtest.h>
#include "OptimizationProblem.hpp"

TEST(OptiProblem, VerifyRosenbrockObjectiveFunction) {
    int number_of_parameters = 2;
    std::vector<std::vector<float> > constraints{{-10, 10}, {-10, 10}};
    EvoAlgos::OptimizationProblem problem = EvoAlgos::OptimizationProblem(number_of_parameters, constraints);
    float example_result = problem.objective_function(std::vector<float>{-1, 3});
    ASSERT_EQ(example_result, 404);
}
