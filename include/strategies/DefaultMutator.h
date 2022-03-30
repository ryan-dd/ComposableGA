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
    void mutate(std::vector<std::vector<entt::entity>>& parents);

private:
    MutatatorInputs inputs;
};

#endif // DEFAULTMUTATOR_H
