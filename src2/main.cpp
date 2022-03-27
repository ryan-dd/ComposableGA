#include <entt/entt.hpp>
#include <functional>
#include <random>
#include <vector>

#include "strategies/DefaultCrossover.h"
#include "strategies/DefaultInitialSolutionGenerator.h"
#include "strategies/DefaultMutator.h"
#include "strategies/DefaultEvaluator.h"
#include "strategies/K_TournamentParentSelector.h"
#include <GA.h>

int main()
{
    // Initialize ECS registry
    entt::registry registry;
    
    // Add parameters
    // Mutator or initialization function for double parameters
    std::mt19937 number_generator(std::random_device{}());
    std::uniform_real_distribution<> dist(-10, 10);
    auto doubleGeneratorFunction = [number_generator, dist, &registry](auto entity) mutable
    {
        registry.emplace<double>(entity, dist(number_generator));
    };

    std::vector<entt::entity> parameters;
    parameters.push_back(addParameter(
        {.mutator = doubleGeneratorFunction,
        .initializer = doubleGeneratorFunction},
        registry));
    parameters.push_back(addParameter(
        {.mutator = doubleGeneratorFunction,
        .initializer = [&registry](auto entity){registry.emplace<double>(entity, 7.3);}},
        registry));

    int a = 1;
    int b = 100;

    auto objFunction = [&registry, a, b](std::vector<entt::entity>& chromosome)
    {
        // Rosenbrock function
        auto x = registry.get<double>(chromosome[0]);
        auto y = registry.get<double>(chromosome[1]);
        return std::pow((a - x), 2) + b*std::pow((y - std::pow(x, 2)), 2);
    };

    // Configure GA
    DefaultEvaluator evaluator({
        .numberOfIterations = 100,
        .objectiveFunction = objFunction,
        .numChromosomes = 12
    }); 

    DefaultInitialSolutionGenerator generator(
        {.numChromosomes = 12,
        .registry = registry, 
        .parameters = parameters});

    auto real_dist = std::uniform_real_distribution<>(0, 1);
    double mutationProbability = 0.01;
    auto mutateCondition = [real_dist, number_generator, mutationProbability]() mutable
    {
        return real_dist(number_generator) < mutationProbability;
    };

    DefaultMutator mutator({
        .mutateCondition = mutateCondition,
        .registry = registry
        });

    K_TournamentParentSelector selector({
        .k = 6,
        .numChromosomes = 12
    });
    
    DefaultCrossover crossover({
        .numParams = static_cast<int>(parameters.size()),
        .crossoverProbability = 0.1
    });

    GA<DefaultInitialSolutionGenerator,
        DefaultEvaluator,
        K_TournamentParentSelector,
        DefaultCrossover,
        DefaultMutator> ga(generator, evaluator, selector, crossover, mutator);
    ga.runGA();
}
