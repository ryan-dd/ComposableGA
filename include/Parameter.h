#ifndef PARAMETER_H
#define PARAMETER_H

#include <entt/entt.hpp>

#include <functional>

using GeneratorFunction = std::function<void(entt::entity)>;

struct ParameterFunctions
{
    GeneratorFunction initializer;
    GeneratorFunction mutator;
};

entt::entity addParameter(const ParameterFunctions& paramFunctions, entt::registry& registry);
entt::entity addParameter(const GeneratorFunction& mutatorAndInitializerfunction, entt::registry& registry);

#endif // PARAMETER_H
