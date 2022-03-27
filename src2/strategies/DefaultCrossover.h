#ifndef DEFAULT_CROSSOVER_H
#define DEFAULT_CROSSOVER_H

#include <random>
#include <vector>
class DefaultCrossover
{
public:
    struct DefaultCrossoverParams
    {
        int numParams;
        double crossoverProbability;
    };

    DefaultCrossover(DefaultCrossoverParams inputParamaters): 
        inputParams(inputParamaters),
        intDistNumParams(0, inputParamaters.numParams),
        realDistribution(0, 1),
        numberGenerator(std::random_device{}())
    {

    }

    void crossover(std::vector<std::vector<entt::entity>> input)
    {
        for (std::size_t i = 0; i < input.size()/2; ++i)
        {
            double probability = realDistribution(numberGenerator);

            if (probability < inputParams.crossoverProbability)
            {
                int crossover_index1 = intDistNumParams(numberGenerator);
                int crossover_index2 = intDistNumParams(numberGenerator);
                std::vector<entt::entity>& first = input[2*i];
                std::vector<entt::entity>& second = input[2*i+1];
                std::swap_ranges(
                    first.begin() + std::min(crossover_index1, crossover_index2), 
                    first.begin() + std::max(crossover_index1, crossover_index2), 
                    second.begin());
            }
        }
    }

private:
    DefaultCrossoverParams inputParams;
    std::uniform_int_distribution<> intDistNumParams;
    std::uniform_real_distribution<> realDistribution;
    std::mt19937_64 numberGenerator;
};

#endif // DEFAULT_CROSSOVER_H
