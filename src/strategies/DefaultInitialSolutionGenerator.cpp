#include "DefaultInitialSolutionGenerator.h"

std::vector<std::vector<entt::entity>> DefaultInitialSolutionGenerator::generate()
{
    std::vector<std::vector<entt::entity>> chromosomes;
    chromosomes.resize(inputs.numChromosomes);

    auto& registry = inputs.registry;
    auto& parameters = inputs.parameters;
    
    for (auto i = 0; i < inputs.numChromosomes; ++i)
    {
        chromosomes.push_back({});
        chromosomes.at(i).resize(parameters.size());
        
        for (auto j = 0u; j < parameters.size(); ++j)
        {
            auto gene = registry.create();
            registry.emplace<entt::entity>(gene, parameters[j]);
            registry.get<ParameterFunctions>(parameters[j]).initializer(gene);
            // TODO Init ref count 1
            chromosomes.at(i).push_back(gene);
        }
    }

    return chromosomes;
}