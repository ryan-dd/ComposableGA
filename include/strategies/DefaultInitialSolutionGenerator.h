#ifndef DEFAULTINITIALSOLUTIONGENERATOR_H
#define DEFAULTINITIALSOLUTIONGENERATOR_H

#include "Parameter.h"

#include <entt/entt.hpp>

#include <vector>

class DefaultInitialSolutionGenerator
{
public:
    struct ChromosomeGeneratorInputs
    {
        int numChromosomes;
        entt::registry& registry;
        std::vector<entt::entity> parameters;
    };

    DefaultInitialSolutionGenerator(ChromosomeGeneratorInputs inputs): inputs(inputs){}
    std::vector<std::vector<entt::entity>> generate();

private:
    ChromosomeGeneratorInputs inputs;
};

#endif // DEFAULTINITIALSOLUTIONGENERATOR_H
