#include "Parameter.h"
#include <iostream>
    
entt::entity addParameter(ParameterFunctions paramFunctions, entt::registry& registry)
{
    auto parameter = registry.create();
    registry.emplace<ParameterFunctions>(parameter, paramFunctions);
    return parameter;
}

entt::entity addParameter(GeneratorFunction mutatorAndInitializerfunction, entt::registry& registry)
{
    auto parameter = registry.create();
    auto functions = ParameterFunctions{
        .initializer = mutatorAndInitializerfunction, 
        .mutator = mutatorAndInitializerfunction
    };
    registry.emplace<ParameterFunctions>(parameter, functions);
    return parameter;
}
