#include "DefaultMutator.h"

void DefaultMutator::mutate(std::vector<std::vector<entt::entity>>& parents)
{
    auto& registry = inputs.registry;
    for (auto& chromosome: parents)
    {
        for (auto i{0u}; i < chromosome.size(); ++i)
        {
            if (inputs.mutateCondition())
            {
                auto gene = chromosome[i];
                auto parameterEntity = registry.get<entt::entity>(gene);
            
                // Replace with new gene
                auto newGene = registry.create();
                registry.emplace<entt::entity>(newGene, parameterEntity);
                registry.get<ParameterFunctions>(parameterEntity).mutator(newGene);
                registry.emplace<int>(newGene, 1);
                chromosome[i] = newGene;
            }
        }
    }
}