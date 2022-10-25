#include "DefaultMutator.h"

DefaultMutator::DefaultMutator(MutatatorInputs inputs):
  inputs(inputs)
{
}

void DefaultMutator::mutate(std::vector<std::vector<entt::entity>>& parents)
{
    auto& registry{inputs.registry};
    for (auto& chromosome: parents)
    {
        for (auto i{0U}; i < chromosome.size(); ++i)
        {
            if (inputs.mutateCondition())
            {
                const auto gene{chromosome[i]};
                const auto parameterEntity{registry.get<entt::entity>(gene)};
            
                // Replace with new gene
                const auto newGene{registry.create()};
                registry.emplace<entt::entity>(newGene, parameterEntity);
                registry.get<ParameterFunctions>(parameterEntity).mutator(newGene);
                chromosome[i] = newGene;
            }
        }
    }
}

