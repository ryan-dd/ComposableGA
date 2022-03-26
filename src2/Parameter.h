#ifndef PARAMETER_H
#define PARAMETER_H

#include <functional>
#include <entt/entt.hpp>

using GeneratorFunction = std::function<void(entt::entity)>;

struct ParameterFunctions
{
    GeneratorFunction mutator;
    GeneratorFunction initializer;
};
    
entt::entity addParameter(ParameterFunctions paramFunctions, entt::registry& registry)
{
    auto parameter = registry.create();
    registry.emplace<ParameterFunctions>(parameter, paramFunctions);
    return parameter;
}

#endif // PARAMETER_H
