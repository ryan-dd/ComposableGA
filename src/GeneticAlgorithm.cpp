#include <algorithm>
#include <iostream>
#include <list>
#include <random>

#include "GeneticAlgorithm.hpp"

EvoAlgos::GeneticAlgorithm::GeneticAlgorithm(int pop_number, int max_iterations, int k_tournament_selection)
{
    this->_max_iterations = max_iterations;
    this->_pop_number = pop_number;
    this->_k_tournament_selection = k_tournament_selection;
    _scores = std::vector<double> (pop_number, 0);
}
    
EvoAlgos::GeneticAlgorithm::~GeneticAlgorithm()
{
}

std::vector<std::vector<double> > EvoAlgos::GeneticAlgorithm::run(EvoAlgos::OptimizationProblem problem)
{
    _starting_population = generate_initial_solutions(problem);
    for (int i = 0; i < _max_iterations; ++i)
    {
        evaluate(_starting_population, problem);
        std::vector<std::vector<double> > new_parents = select_parents();
        _starting_population = new_parents;
    }
    return _starting_population;
}

std::vector<std::vector<double> > EvoAlgos::GeneticAlgorithm::generate_initial_solutions(EvoAlgos::OptimizationProblem problem)
{
    const int& num_parameters = problem.get_num_parameters();
    const auto& constraints = problem.get_constraints();
    std::vector<std::vector<double> > initial_solutions(_pop_number, std::vector<double>(num_parameters, 0));
    std::mt19937 number_generator(std::random_device{}());
    for (int population_index = 0; population_index < _pop_number; ++population_index) {
        for (int parameter_index = 0; parameter_index < num_parameters; ++parameter_index) {
            std::uniform_real_distribution<> dist(constraints[parameter_index][0], constraints[parameter_index][1]);
            initial_solutions[population_index][parameter_index] = dist(number_generator);
        }
    }
    return initial_solutions;
}

void EvoAlgos::GeneticAlgorithm::evaluate(std::vector<std::vector<double> > solution_population, EvoAlgos::OptimizationProblem problem)
{
    for (int i = 0; i < solution_population.size(); ++i)
    {
        _scores[i] = problem.objective_function(solution_population[i]);
    }
}

std::vector<std::vector<double> > EvoAlgos::GeneticAlgorithm::select_parents()
{  
    std::vector<std::vector<double> > parents = std::vector<std::vector<double> >(_pop_number);
    for (int i = 0; i < parents.size(); ++i)
    {
        std::vector<int> run_indices = _pick_random_chromosome(_k_tournament_selection);
        int parent_index = _tournament_selection(run_indices);
        parents[i] = _starting_population[parent_index];
    }
    return parents;
}

int EvoAlgos::GeneticAlgorithm::_tournament_selection(std::vector<int> chromosome_indices)
{
    std::mt19937 gen;
    std::vector<double> selected_scores = std::vector<double>(chromosome_indices.size());
    for (int i = 0; i < selected_scores.size(); ++i)
    {
        selected_scores[i] = _scores[chromosome_indices[i]];
    }
    auto it = std::max_element(selected_scores.begin(), selected_scores.end());
    int max_index = it - selected_scores.begin();
    return chromosome_indices[max_index];
}

std::vector<int> EvoAlgos::GeneticAlgorithm::_pick_random_chromosome(int k)
{
    std::vector<int> indices(_pop_number);
    for (size_t i = 0; i < indices.size(); ++i)
        indices[i] = i;
    
    std::random_device rd;
    std::mt19937 prng(rd());
    std::shuffle(indices.begin(), indices.end(), prng);
    auto first = indices.cbegin();
	auto last = indices.cbegin() + k + 1;

    std::vector<int> random_indices(first, last);
	return random_indices;
}


