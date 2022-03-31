#ifndef DEFAULT_CROSSOVER_H
#define DEFAULT_CROSSOVER_H

#include <entt/entt.hpp>

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

    explicit DefaultCrossover(DefaultCrossoverParams inputParamaters); 
    void crossover(std::vector<std::vector<entt::entity>>& input);

private:
    DefaultCrossoverParams inputParams;
    std::uniform_int_distribution<> intDistNumParams;
    std::uniform_real_distribution<> realDistribution;
    std::mt19937_64 numberGenerator;
};

#endif // DEFAULT_CROSSOVER_H
