#include "K_TournamentParentSelector.h"
#include <iostream>

K_TournamentParentSelector::K_TournamentParentSelector(K_TournamentParentSelectorInputs selectorInputs): 
    inputs(selectorInputs),
    number_generator(std::random_device{}()),
    intDistributionForChromosome(0, selectorInputs.numChromosomes-1),
    cleanupFrequency(30)
{
    randomIndices.resize(inputs.k, 0);
    selectedScores.resize(inputs.k, 0);
}

void K_TournamentParentSelector::selectParents(std::vector<std::vector<entt::entity>>& population, const std::vector<double>& scores)
{
    auto& registry = inputs.registry;
    std::vector<std::vector<entt::entity>> oldPopulation = population;
    
    // When new parents are selected there may be unused genes in the registry, so clean them up periodically
    ++iterations;
    bool doCleanup = iterations % cleanupFrequency == 0; 

    if (doCleanup)
    {
        auto startView = registry.view<entt::entity>();
        for (auto gene: startView) 
        {
            registry.emplace_or_replace<int>(gene, 0);
        }
    }
    
    for (auto& chromosome: population)
    {
        pick_random_chromosomes(inputs.k);
        int parent_index = tournament_selection(scores);
        chromosome = oldPopulation[parent_index];
        
        if(doCleanup)
        {
          // Count how many times each gene is used
          for (auto gene: chromosome)
          {
              registry.get<int>(gene)++; 
          }
        }
    }

    if (doCleanup)
    {
        // Remove genes that are not in use
        auto endView = registry.view<entt::entity>();
        for(auto gene: endView)
        {
            if (registry.get<int>(gene) == 0)
            {
                registry.destroy(gene); 
            }
        }
    }   
}

void K_TournamentParentSelector::pick_random_chromosomes(int number_to_pick)
{
    // Picks random chromosomes indices, allows for duplicates to be chosen
    for (int i = 0; i < number_to_pick; ++i)
    {
        randomIndices[i] = intDistributionForChromosome(number_generator);
    }
}

int K_TournamentParentSelector::tournament_selection(const std::vector<double>& scores)
{
    for (auto i{0U}; i < selectedScores.size(); ++i)
    {
        selectedScores[i] = scores[randomIndices[i]];
    }

    auto it = std::max_element(selectedScores.begin(), selectedScores.end());
    int max_index = it - selectedScores.begin();
    return randomIndices[max_index];
}
