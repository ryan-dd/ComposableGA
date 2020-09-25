#include <gtest/gtest.h>
#include "OptimizationProblem.hpp"

TEST(OptiProblem, VerifyRosenbrockObjectiveFunction) {
    int number_of_parameters = 2;
    std::vector<std::vector<double> > constraints{{-10, 10}, {-10, 10}};
    EvoAlgos::OptimizationProblem problem = EvoAlgos::OptimizationProblem(number_of_parameters, constraints);
    std::vector<double> input{-1, 3};
    double example_result = problem.objective_function(input);
    ASSERT_EQ(example_result, 404);
}

TEST(OptiProblem, InputParameterValidation) {
    int number_of_parameters = 2;
    std::vector<std::vector<double> > constraints{{-10}, {-10, 10}};
    ASSERT_THROW({
        try {
            EvoAlgos::OptimizationProblem(number_of_parameters, constraints);
        }
        catch(const std::exception& e) {
            ASSERT_EQ(e.what(), EvoAlgos::OptimizationProblem::CONSTRAINT_SIZE_ERROR_MSG);
            throw;
        }    
    }, std::runtime_error);
}
