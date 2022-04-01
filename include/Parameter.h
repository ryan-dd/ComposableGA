#ifndef PARAMETER_H
#define PARAMETER_H

#include <entt/entt.hpp>

#include <functional>

using GeneratorFunction = std::function<void(entt::entity)>;

struct ParameterFunctions
{
    GeneratorFunction mutator;
    GeneratorFunction initializer;
};

entt::entity addParameter(ParameterFunctions paramFunctions, entt::registry& registry);
entt::entity addParameter(GeneratorFunction mutatorAndInitializerfunction, entt::registry& registry);

#endif // PARAMETER_H
