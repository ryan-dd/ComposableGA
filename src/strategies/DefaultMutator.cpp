#include "DefaultMutator.h"

void DefaultMutator::mutate(std::vector<std::vector<entt::entity>> parents)
{
    for (auto& chromosome: parents)
    {
        for (auto gene: chromosome)
        {
            if (inputs.mutateCondition())
            {
                // TODO Replace gene with deep copy of itself on mutation
                auto parameterEntity = inputs.registry.get<entt::entity>(gene);
                inputs.registry.get<ParameterFunctions>(parameterEntity).mutator(gene);
            }
        }
    }

    // TODO Clean up vars with ref count 0
}