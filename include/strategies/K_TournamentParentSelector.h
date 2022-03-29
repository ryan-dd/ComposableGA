#ifndef K_TOURNAMENT_PARENT_SELECTOR
#define K_TOURNAMENT_PARENT_SELECTOR

#include <vector>
#include <entt/entt.hpp>
#include <random>

class K_TournamentParentSelector
{
public:
    struct K_TournamentParentSelectorInputs
    {   
        int k = 0;
        int numChromosomes = 0;
        entt::registry& registry;
    };

    K_TournamentParentSelector(K_TournamentParentSelectorInputs selectorInputs);
    void selectParents(std::vector<std::vector<entt::entity>>& population, const std::vector<double>& scores);
    void pick_random_chromosomes(int number_to_pick);
    int tournament_selection(const std::vector<double>& scores);

private:
    K_TournamentParentSelectorInputs inputs;
    std::mt19937_64 number_generator;
    std::uniform_int_distribution<> intDistributionForChromosome;
    std::vector<int> randomIndices;
    std::vector<double> selectedScores;
};

#endif // K_TOURNAMENT_PARENT_SELECTOR
