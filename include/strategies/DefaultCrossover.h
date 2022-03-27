#ifndef DEFAULT_CROSSOVER_H
#define DEFAULT_CROSSOVER_H

#include <random>
#include <vector>
#include <entt/entt.hpp>

class DefaultCrossover
{
public:
    struct DefaultCrossoverParams
    {
        int numParams;
        double crossoverProbability;
    };

    DefaultCrossover(DefaultCrossoverParams inputParamaters); 
    void crossover(std::vector<std::vector<entt::entity>> input);

private:
    DefaultCrossoverParams inputParams;
    std::uniform_int_distribution<> intDistNumParams;
    std::uniform_real_distribution<> realDistribution;
    std::mt19937_64 numberGenerator;
};

#endif // DEFAULT_CROSSOVER_H
