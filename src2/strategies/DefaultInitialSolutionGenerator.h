#ifndef DEFAULTINITIALSOLUTIONGENERATOR_H
#define DEFAULTINITIALSOLUTIONGENERATOR_H

#include "Parameter.h"

#include <vector>
#include <entt/entt.hpp>

class DefaultInitialSolutionGenerator
{
public:
    struct ChromosomeGeneratorInputs
    {
        std::size_t numChromosomes;
        entt::registry& registry;
        std::vector<entt::entity> parameters;
    };

    DefaultInitialSolutionGenerator(ChromosomeGeneratorInputs inputs): inputs(inputs){}
    
    std::vector<std::vector<entt::entity>> generate()
    {
        std::vector<std::vector<entt::entity>> chromosomes;
        chromosomes.resize(inputs.numChromosomes);

        auto& registry = inputs.registry;
        auto& parameters = inputs.parameters;
        
        for (auto i = 0u; i < inputs.numChromosomes; ++i)
        {
            chromosomes.push_back({});
            chromosomes.at(i).resize(parameters.size());
            
            for (auto j = 0u; j < parameters.size(); ++j)
            {
                auto gene = registry.create();
                registry.emplace<entt::entity>(gene, parameters[j]);
                registry.get<ParameterFunctions>(parameters[j]).initializer(gene);
                chromosomes.at(i).push_back(gene);
            }
        }

        return chromosomes;
    }

private:
    ChromosomeGeneratorInputs inputs;
};

#endif // DEFAULTINITIALSOLUTIONGENERATOR_H
