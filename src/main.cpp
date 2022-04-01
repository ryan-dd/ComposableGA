#include "DefaultGA.h"
#include "Parameter.h"

#include <entt/entt.hpp>

#include <functional>
#include <random>
#include <vector>
#include <iostream>

int main()
{
    // Initialize ECS registry
    entt::registry registry;
    
    // Initialize mutation and initialization functions for parameters of type double
    std::mt19937 number_generator(std::random_device{}());
    std::uniform_real_distribution<> dist(-10, 10);
    auto doubleGeneratorFunction = [number_generator, dist, &registry](auto entity) mutable
    {
        registry.emplace<double>(entity, dist(number_generator));
    };
    
    constexpr double constantInitialValue = 9;
    auto constantInitializer = [&registry, constantInitialValue](auto entity)
    {
        registry.emplace<double>(entity, constantInitialValue);
    };

    // Initialize parameters for objective function
    std::vector<entt::entity> parameters
    {
        addParameter({.mutator = doubleGeneratorFunction,
                    .initializer = doubleGeneratorFunction},
                    registry),
        addParameter({.mutator = doubleGeneratorFunction,
                    .initializer = constantInitializer},
                    registry)
    };

    // Initialize objective function
    constexpr double a = 1;
    constexpr double b = 100;
    auto objFunction = [&registry](std::vector<entt::entity>& chromosome)
    {
        // Rosenbrock function
        auto x = registry.get<double>(chromosome[0]);
        auto y = registry.get<double>(chromosome[1]);
        return -(std::pow((a - x), 2) + b*std::pow((y - std::pow(x, 2)), 2));
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
