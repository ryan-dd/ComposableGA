#include "DefaultGA.h"

DefaultGA configureDefaultGA(DefaultGA_Params params, entt::registry& registry)
{
    DefaultInitialSolutionGenerator generator({
        .numChromosomes = params.numChromosomes,
        .registry = registry, 
        .parameters = params.parameters
    });

    DefaultEvaluator evaluator({
        .objectiveFunction = params.objectiveFunction,
        .numberOfIterations = params.numIterations,
        .numChromosomes = params.numChromosomes,
    }); 

    K_TournamentParentSelector selector({
        .k = params.k_numberTournamentSelection,
        .numChromosomes = params.numChromosomes,
        .registry = registry
    });

    DefaultCrossover crossover({
        .numParams = static_cast<int>(params.parameters.size()),
        .crossoverProbability = params.crossoverProbability
    });
    
    // Mutation condition is when random number is less than the mutation probability
    auto real_dist{std::uniform_real_distribution<>(0.0, 1.0)};
    std::mt19937 number_generator(std::random_device{}());
    DefaultMutator mutator({
        .mutateCondition = [real_dist, number_generator, mutationProb = params.mutationProbability]() mutable 
        { return real_dist(number_generator) < mutationProb; },
        .registry = registry
    });

    return {generator, evaluator, selector, crossover, mutator};
}
