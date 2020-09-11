#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include "OptimizationProblem.hpp"

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

        std::vector<int> _pick_random_chromosome(int k);
        int _tournament_selection(std::vector<int> chromosome_indices);
        std::vector<double> _get_best_chromosome();

    public:
        GeneticAlgorithm(int pop_number, int max_iterations, int k_tournament_selection, double crossover_probability, double mutation_probability);
        ~GeneticAlgorithm();
        std::vector<double> run(EvoAlgos::OptimizationProblem problem);

        std::vector<std::vector<double> > generate_initial_solutions(EvoAlgos::OptimizationProblem problem);
        void evaluate(std::vector<std::vector<double> > solution_population, EvoAlgos::OptimizationProblem problem);
        std::vector<std::vector<double> > select_parents();
        std::vector<std::vector<double> > crossover(std::vector<std::vector<double> > population);
        std::vector<std::vector<double> > mutate(std::vector<std::vector<double> > population, EvoAlgos::OptimizationProblem problem);
    };
    
}
#endif 
