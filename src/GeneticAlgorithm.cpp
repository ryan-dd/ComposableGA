#include <algorithm>
#include <iostream>
#include <random>

#include "GeneticAlgorithm.hpp"

EvoAlgos::GeneticAlgorithm::GeneticAlgorithm(int pop_number, int max_iterations)
{
    this->max_iterations = max_iterations;
    this->pop_number = pop_number;
    _scores = std::vector<double> (pop_number, 0);
}
    
EvoAlgos::GeneticAlgorithm::~GeneticAlgorithm()
{
}

std::vector<std::vector<double> > EvoAlgos::GeneticAlgorithm::run(EvoAlgos::OptimizationProblem problem)
{
    _starting_population = generate_initial_solutions(problem);
    for (int i = 0; i < max_iterations; ++i)
    {
        evaluate(_starting_population, problem);
    }
    return _starting_population;
}

std::vector<std::vector<double> > EvoAlgos::GeneticAlgorithm::generate_initial_solutions(EvoAlgos::OptimizationProblem problem)
{
    int num_parameters = problem.get_num_parameters();
    auto constraints = problem.get_constraints();
    std::vector<std::vector<double>> initial_solutions(pop_number, std::vector<double>(num_parameters, 0));

    // Initialize Mersenne Twister random number generator
    std::mt19937 number_generator(std::random_device{}());
    for (int population_index = 0; population_index < pop_number; ++population_index) {
        for (int parameter_index = 0; parameter_index < num_parameters; ++parameter_index) {
            std::uniform_real_distribution<> dist(constraints[parameter_index][0], constraints[parameter_index][1]);
            initial_solutions[population_index][parameter_index] = dist(number_generator);
            
        }
    }
    return initial_solutions;
}

void EvoAlgos::GeneticAlgorithm::evaluate(std::vector<std::vector<double> > solution_population, EvoAlgos::OptimizationProblem problem)
{
    for (int i = 0; i < solution_population.size(); i++)
    {
        _scores[i] = problem.objective_function(solution_population[i]);
    }
}