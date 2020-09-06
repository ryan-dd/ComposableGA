#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <OptimizationProblem.hpp>

namespace EvoAlgos{
    class GeneticAlgorithm
    {
    private:
        std::vector<std::vector<float> > evaluation();
        std::vector<std::vector<float> > crossover();
        std::vector<std::vector<float> > mutation();
        std::vector<std::vector<float> > selection();

        std::vector<float> mScores;
    public:
        GeneticAlgorithm();
        ~GeneticAlgorithm();
        std::vector<std::vector<float> > run(EvoAlgos::OptimizationProblem problem);
    };
    
}
#endif 