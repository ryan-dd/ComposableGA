#include "DefaultCrossover.h"
#include <iostream>

DefaultCrossover::DefaultCrossover(DefaultCrossoverParams inputParamaters): 
        inputParams(inputParamaters),
        intDistNumParams(0, inputParamaters.numParams - 1),
        realDistribution(0, 1),
        numberGenerator(std::random_device{}())
{

}

void DefaultCrossover::crossover(std::vector<std::vector<entt::entity>>& input)
{
    for (auto i = 0U; i < input.size()/2; ++i)
    {
        double probability = realDistribution(numberGenerator);

        if (probability < inputParams.crossoverProbability)
        {
            int crossover_index1 = intDistNumParams(numberGenerator);
            int crossover_index2 = intDistNumParams(numberGenerator);
            auto beginIndex = std::min(crossover_index1, crossover_index2);
            auto endIndex = std::max(crossover_index1, crossover_index2) + 1;
            
            std::vector<entt::entity>& first = input[2*i];
            std::vector<entt::entity>& second = input[2*i+1];
            
            std::swap_ranges(
                first.begin() + beginIndex, 
                first.begin() + endIndex, 
                second.begin() + beginIndex);
        }
    }
}