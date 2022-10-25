#include "Parameter.h"
    
entt::entity addParameter(const ParameterFunctions& paramFunctions, entt::registry& registry)
{
    const auto parameter {registry.create()};
    registry.emplace<ParameterFunctions>(parameter, paramFunctions);
    return parameter;
}

entt::entity addParameter(const GeneratorFunction& mutatorAndInitializerfunction, entt::registry& registry)
{
    auto functions{ParameterFunctions{
        .initializer = mutatorAndInitializerfunction, 
        .mutator = mutatorAndInitializerfunction
    }};
    return addParameter(functions, registry);
}
