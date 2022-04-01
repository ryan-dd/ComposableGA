#include "DefaultGA.h"
#include "Parameter.h"

#include <entt/entt.hpp>

#include <functional>
#include <random>
#include <vector>
#include <iostream>

TEST(Integration, TestBoolAndDoubles) {
    entt::registry registry;
    std::mt19937 number_generator(std::random_device{}());
    std::uniform_real_distribution<> doubleDist(-10, 10);
    auto doubleGeneratorFunction = [number_generator, doubleDist, &registry](auto entity) mutable
    {
        registry.emplace<double>(entity, dist(number_generator));
    };

    std::uniform_real_distribution<> boolDist(0, 1);
    auto boolGeneratorFunction = [number_generator, boolDist, &registry](auto entity) mutable
    {
        registry.emplace<double>(entity, boolDist(number_generator));
    };

    // Initialize parameters for objective function
    std::vector<entt::entity> parameters;
    int numParamSets = 5;

    for(auto i{0}; i < numParamSets; ++i)
    {
        parameters.push_back(addParameter(boolGeneratorFunction, registry));
        parameters.push_back(addParameter(doubleGeneratorFunction, registry));
    }

    // The bool 
    auto objFunction = [&registry, numParamSet](std::vector<entt::entity>& chromosome)
    {
        double score = 0.0;
        for(auto i{0}; i < numParamSet; ++i)
        {
            if(registry.get<bool>chromosome.at(2*i))
            {
                score += registry.get<double>chromosome.at(2*i+1);
            }
        }

        return score;
    };

    // Configure GA
    auto ga = configureDefaultGA({
        .objectiveFunction = objFunction,
        .parameters = parameters,
        .numIterations = 100,
        .numChromosomes = 10000,
        .k_numberTournamentSelection = 5,
        .mutationProbability = 0.08,
        .crossoverProbability = 0.05
    }, registry);
    
    auto bestChromosome = ga.runGA();
    std::cout << "Param 1" << registry.get<double>(bestChromosome.at(0)) << '\n';
    std::cout << "Param 2" << registry.get<double>(bestChromosome.at(1)) << '\n';
    std::cout << "Score: " << objFunction(bestChromosome);

    return 0;
}
