#ifndef K_TOURNAMENT_PARENT_SELECTOR
#define K_TOURNAMENT_PARENT_SELECTOR

#include <entt/entt.hpp>

#include <random>
#include <vector>

class K_TournamentParentSelector
{
public:
    struct K_TournamentParentSelectorInputs
    {   
        int k{};
        int numChromosomes{};
        entt::registry& registry;
    };

    explicit K_TournamentParentSelector(K_TournamentParentSelectorInputs selectorInputs);
    void selectParents(std::vector<std::vector<entt::entity>>& population, const std::vector<double>& scores);
    void pickRandomChromosomes(int number_to_pick);
    int tournamentSelection(const std::vector<double>& scores);
    void setCleanupFrequency(int cleanupFrequency);

private:
    const K_TournamentParentSelectorInputs inputs;
    std::mt19937_64 numberGenerator;
    std::uniform_int_distribution<> intDistributionForChromosome;
    std::vector<int> randomIndices{};
    std::vector<double> selectedScores{};
    int cleanupFrequency{30};
    int iterations{0};
};

#endif // K_TOURNAMENT_PARENT_SELECTOR
