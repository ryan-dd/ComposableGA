#include "DefaultInitialSolutionGenerator.h"

std::vector<std::vector<entt::entity>> DefaultInitialSolutionGenerator::generate()
{
    std::vector<std::vector<entt::entity>> chromosomes;
    chromosomes.resize(inputs.numChromosomes);

    auto& registry = inputs.registry;
    auto& parameters = inputs.parameters;
    
    for (auto i = 0; i < inputs.numChromosomes; ++i)
    {
        for (auto j{0U}; j < parameters.size(); ++j)
        {
            auto gene = registry.create();
            registry.emplace<entt::entity>(gene, parameters[j]);
            registry.get<ParameterFunctions>(parameters[j]).initializer(gene);
            registry.emplace<int>(gene, 1);
            chromosomes.at(i).push_back(gene);
        }
    }

    return chromosomes;
}