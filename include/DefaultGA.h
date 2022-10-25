#ifndef DEFAULTGA_H
#define DEFAULTGA_H

#include <GA.h>
#include <strategies/DefaultCrossover.h>
#include <strategies/DefaultEvaluator.h>
#include <strategies/DefaultInitialSolutionGenerator.h>
#include <strategies/DefaultMutator.h>
#include <strategies/K_TournamentParentSelector.h>

#include <entt/entt.hpp>

#include <functional>
#include <vector>
#include <random>

struct DefaultGA_Params
{
    int numIterations;
    int numChromosomes;
    int k_numberTournamentSelection;
    double mutationProbability;
    double crossoverProbability;
    std::function<double(std::vector<entt::entity>&)> objectiveFunction;
    std::vector<entt::entity> parameters;
};

using DefaultGA = GA<DefaultInitialSolutionGenerator,
                    DefaultEvaluator,
                    K_TournamentParentSelector,
                    DefaultCrossover,
                    DefaultMutator>;

DefaultGA configureDefaultGA(const DefaultGA_Params& params, entt::registry& registry);

#endif // DEFAULTGA_H
