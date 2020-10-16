#include <algorithm>
#include <cstddef>
#include <iostream>
#include <list>

#include "GeneticAlgorithm.hpp"

EvoAlgos::GeneticAlgorithm::GeneticAlgorithm(int pop_number, int max_iterations, int k_tournament_selection, double crossover_probability, double mutation_probability)
{
    this->_max_iterations = max_iterations;
    this->_pop_number = pop_number;
    this->_k_tournament_selection = k_tournament_selection;
    this->_crossover_probability = crossover_probability;
    this->_mutation_probability = mutation_probability;
    _scores = std::vector<double> (pop_number, 0);
    number_generator = std::mt19937_64 (std::random_device{}());
    parents = std::vector<std::vector<double>> (_pop_number);
    random_indices = std::vector<int> (k_tournament_selection);
    selected_scores = std::vector<double>(k_tournament_selection);

    real_dist = std::uniform_real_distribution<>(0, 1);
    int_dist_population = std::uniform_int_distribution<>(0, _pop_number-1);
}
    
EvoAlgos::GeneticAlgorithm::~GeneticAlgorithm()
{
}

std::vector<double> EvoAlgos::GeneticAlgorithm::run(EvoAlgos::OptimizationProblem problem)
{
    int_dist_chromosome = std::uniform_int_distribution<>(0, problem.get_num_parameters()-1);
    _current_population = generate_initial_solutions(problem);
    for (int i = 0; i < _max_iterations; ++i)
    {
        evaluate(_current_population, problem);
        select_parents();
        crossover();
        mutate(problem);
        _current_population = parents;
    }

    return _get_best_chromosome();
}

std::vector<std::vector<double> > EvoAlgos::GeneticAlgorithm::generate_initial_solutions(EvoAlgos::OptimizationProblem problem)
{
    const int num_parameters = problem.get_num_parameters();
    const auto& constraints = problem.get_constraints();
    std::vector<std::vector<double> > initial_solutions(_pop_number, std::vector<double>(num_parameters, 0));
    std::mt19937 number_generator(std::random_device{}());
    for (int parameter_index = 0; parameter_index < num_parameters; ++parameter_index) {
        std::uniform_real_distribution<> dist(constraints[parameter_index][0], constraints[parameter_index][1]);
        for (int population_index = 0; population_index < _pop_number; ++population_index) {
            initial_solutions[population_index][parameter_index] = dist(number_generator);
        }
    }
    return initial_solutions;
}

void EvoAlgos::GeneticAlgorithm::evaluate(std::vector<std::vector<double>>& solution_population, EvoAlgos::OptimizationProblem problem)
{
    for (std::size_t i = 0; i < solution_population.size(); ++i)
    {
        _scores[i] = problem.objective_function(solution_population[i]);
    }
}

void EvoAlgos::GeneticAlgorithm::select_parents()
{  
    for (std::size_t i = 0; i < parents.size(); ++i)
    {
        _pick_random_chromosome(_k_tournament_selection);
        int parent_index = _tournament_selection();
        parents[i] = _current_population[parent_index];
    }
}

void EvoAlgos::GeneticAlgorithm::_pick_random_chromosome(int number_to_pick)
{
    // Picks random chromosomes indices, allows for duplicates to be chosen
    for (int i = 0; i < number_to_pick; ++i)
        random_indices[i] = int_dist_population(number_generator);
}

int EvoAlgos::GeneticAlgorithm::_tournament_selection()
{
    for (std::size_t i = 0; i < selected_scores.size(); ++i)
    {
        selected_scores[i] = _scores[random_indices[i]];
    }
    auto it = std::max_element(selected_scores.begin(), selected_scores.end());
    int max_index = it - selected_scores.begin();
    return random_indices[max_index];
}

void EvoAlgos::GeneticAlgorithm::crossover()
{
    for (std::size_t i = 0; i < parents.size()/2; ++i)
    {
        double probability = real_dist(number_generator);
        if (probability < _crossover_probability)
        {
            int crossover_index = int_dist_chromosome(number_generator);
            std::vector<double>& first = parents[2*i];
            std::vector<double>& second = parents[2*i+1];
            std::swap_ranges(first.begin(), first.begin()+crossover_index+1, second.begin());
        }

    }
}

void EvoAlgos::GeneticAlgorithm::mutate(EvoAlgos::OptimizationProblem problem)
{
    for (std::size_t i = 0; i < parents.size(); ++i)
    {
        double probability = real_dist(number_generator);
        if (probability < _mutation_probability)
        {
            std::vector<double>& chromosome = parents[i];
            int mutation_index = int_dist_chromosome(number_generator);
            double number = real_dist(number_generator);
            double lower_bound = problem.get_constraints()[mutation_index][0];
            double upper_bound = problem.get_constraints()[mutation_index][1];
            chromosome[mutation_index] = number*(upper_bound-lower_bound)+lower_bound;
        }
    }
}

std::vector<double> EvoAlgos::GeneticAlgorithm::_get_best_chromosome()
{
    auto it = std::max_element(_scores.begin(), _scores.end());
    int max_index = it - _scores.begin();
    return _current_population[max_index];
}
