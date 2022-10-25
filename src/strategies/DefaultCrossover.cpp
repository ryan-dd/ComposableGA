#include "DefaultCrossover.h"

DefaultCrossover::DefaultCrossover(DefaultCrossoverParams inputParameters): 
        inputParams {inputParameters},
        intDistNumParams(0, inputParameters.numParams - 1),
        realDistribution(0.0, 1.0),
        numberGenerator(std::random_device{}())
{
}

void DefaultCrossover::crossover(std::vector<std::vector<entt::entity>>& input)
{
    for (auto i{0U}; i < input.size()/2; ++i)
    {
        const auto probability {realDistribution(numberGenerator)};

        if (probability < inputParams.crossoverProbability)
        {
            const auto crossover_index1 {intDistNumParams(numberGenerator)};
            const auto crossover_index2 {intDistNumParams(numberGenerator)};
            const auto beginIndex {std::min(crossover_index1, crossover_index2)};
            const auto endIndex {std::max(crossover_index1, crossover_index2) + 1};
            
            auto& first {input[2*i]};
            auto& second {input[2*i+1]};
            
            std::swap_ranges(
                first.begin() + beginIndex, 
                first.begin() + endIndex, 
                second.begin() + beginIndex);
        }
    }
}
