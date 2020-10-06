#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include "OptimizationProblem.hpp"
#include <random>

namespace EvoAlgos{
    class GeneticAlgorithm
    {
    private:
        std::vector<double> _scores;
        std::vector<std::vector<double> > _current_population;
        int _pop_number;
        int _max_iterations;
        int _k_tournament_selection;
        double _crossover_probability;
        double _mutation_probability;
        std::vector<int> random_indices;
        std::vector<double>selected_scores;
        std::mt19937 number_generator;
        std::uniform_int_distribution<> int_dist_chromosome;
        std::uniform_int_distribution<> int_dist_population;
        std::uniform_real_distribution<> real_dist;
        std::vector<std::vector<double>> parents;

        void _pick_random_chromosome(int k);
        int _tournament_selection();
        std::vector<double> _get_best_chromosome();

    public:
        GeneticAlgorithm(int pop_number, int max_iterations, int k_tournament_selection, double crossover_probability, double mutation_probability);
        ~GeneticAlgorithm();
        std::vector<double> run(EvoAlgos::OptimizationProblem problem);

        std::vector<std::vector<double> > generate_initial_solutions(EvoAlgos::OptimizationProblem problem);
        void evaluate(std::vector<std::vector<double>> solution_population, EvoAlgos::OptimizationProblem problem);
        void select_parents();
        void crossover();
        void mutate(EvoAlgos::OptimizationProblem problem);
    };
    
}
#endif 
