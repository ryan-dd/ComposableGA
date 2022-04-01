#include "DefaultGA.h"
#include "Parameter.h"

#include <entt/entt.hpp>

#include <functional>
#include <random>
#include <vector>
#include <iostream>

int main()
{
    entt::registry registry;
    std::mt19937 number_generator(std::random_device{}());
    std::uniform_real_distribution<> doubleDist(-100, 100);
    auto doubleGeneratorFunction = [number_generator, doubleDist, &registry](auto entity) mutable
    {
        registry.emplace<double>(entity, doubleDist(number_generator));
    };

    std::uniform_real_distribution<> boolDist(0, 1);
    auto boolGeneratorFunction = [number_generator, boolDist, &registry](auto entity) mutable
    {
        registry.emplace<bool>(entity, boolDist(number_generator));
    };

    // Initialize parameters for objective function
    std::vector<entt::entity> parameters;
    constexpr int numParamSets = 10;

    for(auto i{0}; i < numParamSets; ++i)
    {
        parameters.push_back(addParameter(boolGeneratorFunction, registry));
        parameters.push_back(addParameter(doubleGeneratorFunction, registry));
    }

    // The bool "activates" the double and makes it a part of the score
    auto objFunction = [&registry](std::vector<entt::entity>& chromosome)
    {
        double score = 0.0;
        for(auto i{0}; i < numParamSets; ++i)
        {
            if(registry.get<bool>(chromosome.at(2*i)))
            {
                score += registry.get<double>(chromosome.at(2*i+1));
            }
        }

        return score;
    };

    // Configure GA
    auto ga = configureDefaultGA({
        .objectiveFunction = objFunction,
        .parameters = parameters,
        .numIterations = 100,
        .numChromosomes = 1000,
        .k_numberTournamentSelection = 5,
        .mutationProbability = 0.08,
        .crossoverProbability = 0.05
    }, registry);
    
    auto bestChromosome = ga.runGA();

    for(auto i{0}; i < numParamSets; ++i)
    {
        std::cout << registry.get<bool>(bestChromosome.at(2*i)) << "; ";
        std::cout << registry.get<double>(bestChromosome.at(2*i+1)) << "\n";
    }

    std::cout << "Score: " << objFunction(bestChromosome);

    return 0;
}
