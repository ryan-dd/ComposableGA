#ifndef K_TOURNAMENT_PARENT_SELECTOR
#define K_TOURNAMENT_PARENT_SELECTOR

class K_TournamentParentSelector
{
public:
    struct K_TournamentParentSelectorInputs
    {   
        int k = 0;
        int numChromosomes = 0;
    };

    K_TournamentParentSelector(K_TournamentParentSelectorInputs selectorInputs): 
        inputs(selectorInputs),
        number_generator(std::random_device{}()),
        intDistributionForChromosome(0, selectorInputs.numChromosomes)
    {
        randomIndices.resize(inputs.k, 0);
    }
    
    // TODO change double to comparable concept
    void selectParents(std::vector<std::vector<entt::entity>>& population, const std::vector<double>& scores)
    {
        std::vector<std::vector<entt::entity>> oldPopulation = population;

        for (auto i = 0u; i < population.size(); ++i)
        {
            pick_random_chromosomes(inputs.k);
            int parent_index = tournament_selection(scores);
            population[i] = oldPopulation[parent_index];
            
            for (auto gene: population[i])
            {
                // registry.get<int>(gene)++; add ref count
            }
        }
    };

    void pick_random_chromosomes(int number_to_pick)
    {
        // Picks random chromosomes indices, allows for duplicates to be chosen
        for (int i = 0; i < number_to_pick; ++i)
        {
            randomIndices[i] = intDistributionForChromosome(number_generator);
        }
    }

    int tournament_selection(const std::vector<double>& scores)
    {
        for (auto i = 0u; i < selectedScores.size(); ++i)
        {
            selectedScores[i] = scores[randomIndices[i]];
        }

        auto it = std::max_element(selectedScores.begin(), selectedScores.end());
        int max_index = it - selectedScores.begin();
        return randomIndices[max_index];
    }
private:
    K_TournamentParentSelectorInputs inputs;
    std::mt19937_64 number_generator;
    std::uniform_int_distribution<> intDistributionForChromosome;
    std::vector<int> randomIndices;
    std::vector<double> selectedScores;
};

#endif // K_TOURNAMENT_PARENT_SELECTOR
