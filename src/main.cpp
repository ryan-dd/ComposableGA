#include "strategies/DefaultCrossover.h"
#include "strategies/DefaultInitialSolutionGenerator.h"
#include "strategies/DefaultMutator.h"
#include "strategies/DefaultEvaluator.h"
#include "strategies/K_TournamentParentSelector.h"
#include "GA.h"
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
    
    // Initialize mutator or initialization function for parameters of type double
    std::mt19937 number_generator(std::random_device{}());
    std::uniform_real_distribution<> dist(-10, 10);
    auto doubleGeneratorFunction = [number_generator, dist, &registry](auto entity) mutable
    {
        registry.emplace<double>(entity, dist(number_generator));
    };

    std::vector<entt::entity> parameters;
    parameters.push_back(addParameter({
        .mutator = doubleGeneratorFunction,
        .initializer = doubleGeneratorFunction
        },
        registry));

    double constantInitialValue = 9;
    parameters.push_back(addParameter({
        .mutator = doubleGeneratorFunction,
        .initializer = [&registry, constantInitialValue](auto entity){
            registry.emplace<double>(entity, constantInitialValue);
        }},
        registry));

    // Initialize objective function
    double a = 1;
    double b = 100;
    auto objFunction = [&registry, a, b](std::vector<entt::entity>& chromosome)
    {
        // Rosenbrock function
        auto x = registry.get<double>(chromosome[0]);
        auto y = registry.get<double>(chromosome[1]);
        return -(std::pow((a - x), 2) + b*std::pow((y - std::pow(x, 2)), 2));
    };

    // Configure GA
    int numChromosomes = 10000;
    DefaultEvaluator evaluator({
        .numberOfIterations = 100,
        .objectiveFunction = objFunction,
        .numChromosomes = numChromosomes,
    }); 

    DefaultInitialSolutionGenerator generator(
        {.numChromosomes = numChromosomes,
        .registry = registry, 
        .parameters = parameters});

    auto real_dist = std::uniform_real_distribution<>(0, 1);
    double mutationProbability = 0.08;
    DefaultMutator mutator({
        .mutateCondition = [real_dist, number_generator, mutationProbability]() mutable {
            return real_dist(number_generator) < mutationProbability;
        },
        .registry = registry
        });

    K_TournamentParentSelector selector({
        .k = 5,
        .numChromosomes = numChromosomes,
        .registry = registry
    });

    DefaultCrossover crossover({
        .numParams = static_cast<int>(parameters.size()),
        .crossoverProbability = 0.05
    });

    GA<DefaultInitialSolutionGenerator,
        DefaultEvaluator,
        K_TournamentParentSelector,
        DefaultCrossover,
        DefaultMutator> ga(generator, evaluator, selector, crossover, mutator);
    
    auto bestChromosome = ga.runGA();
    std::cout << "Param 1" << registry.get<double>(bestChromosome.at(0)) << '\n';
    std::cout << "Param 2" << registry.get<double>(bestChromosome.at(1)) << '\n';
    std::cout << "Score: " << objFunction(bestChromosome);
}
