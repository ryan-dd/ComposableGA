#include "Parameter.h"
#include <iostream>
    
entt::entity addParameter(ParameterFunctions paramFunctions, entt::registry& registry)
{
    const auto parameter{registry.create()};
    registry.emplace<ParameterFunctions>(parameter, paramFunctions);
    return parameter;
}

entt::entity addParameter(GeneratorFunction mutatorAndInitializerfunction, entt::registry& registry)
{
    const auto parameter{registry.create()};
    const auto functions{ParameterFunctions{
        .initializer = mutatorAndInitializerfunction, 
        .mutator = mutatorAndInitializerfunction
    }};
    registry.emplace<ParameterFunctions>(parameter, functions);
    return parameter;
}
