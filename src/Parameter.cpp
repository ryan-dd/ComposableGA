#include "Parameter.h"
#include <iostream>
    
entt::entity addParameter(ParameterFunctions paramFunctions, entt::registry& registry)
{
    auto parameter = registry.create();
    registry.emplace<ParameterFunctions>(parameter, paramFunctions);
    
    return parameter;
}
