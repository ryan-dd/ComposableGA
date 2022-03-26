#ifndef DEFAULTMUTATOR_H
#define DEFAULTMUTATOR_H

#include "Parameter.h"

#include <functional>
#include <entt/entt.hpp>

class DefaultMutator
{
public:
    struct MutatatorInputs
    {
        std::function<bool()> mutateCondition;
        entt::registry& registry;
    };

    DefaultMutator(MutatatorInputs inputs): inputs(inputs){}

    void mutate(std::vector<std::vector<entt::entity>> parents)
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

private:
    MutatatorInputs inputs;
};

#endif // DEFAULTMUTATOR_H
