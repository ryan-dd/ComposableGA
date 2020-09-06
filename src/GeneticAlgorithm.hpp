#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include "OptimizationProblem.hpp"

namespace EvoAlgos{
    class GeneticAlgorithm
    {
    private:
        std::vector<double> _scores;
        std::vector<std::vector<double> > _starting_population;
        int pop_number;
        int max_iterations;

    public:
        GeneticAlgorithm(int pop_number, int max_iterations);
        ~GeneticAlgorithm();
        std::vector<std::vector<double> > run(EvoAlgos::OptimizationProblem problem);

        std::vector<std::vector<double> > generate_initial_solutions(EvoAlgos::OptimizationProblem problem);
        void evaluate(std::vector<std::vector<double> > solution_population, EvoAlgos::OptimizationProblem problem);
        std::vector<std::vector<double> > select_parents();
        std::vector<std::vector<double> > crossover();
        std::vector<std::vector<double> > mutate();
    };
    
}
#endif 