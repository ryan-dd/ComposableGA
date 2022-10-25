#include "DefaultInitialSolutionGenerator.h"

DefaultInitialSolutionGenerator::DefaultInitialSolutionGenerator(ChromosomeGeneratorInputs inputs): 
  inputs {std::move(inputs)}
{
}

std::vector<std::vector<entt::entity>> DefaultInitialSolutionGenerator::generate()
{
    std::vector<std::vector<entt::entity>> chromosomes {};
    chromosomes.resize(inputs.numChromosomes);

    auto& registry {inputs.registry};
    const auto& parameters {inputs.parameters};
    
    for (auto i {0}; i < inputs.numChromosomes; ++i)
    {
        for (auto j {0U}; j < parameters.size(); ++j)
        {
            const auto gene {registry.create()};

            // Associate the gene with its parameter type
            // Parameter is also represented by an entt::entity
            registry.emplace<entt::entity>(gene, parameters[j]); 

            // Initialize the gene with the parameter type's initializer function
            registry.get<ParameterFunctions>(parameters[j]).initializer(gene); 
            chromosomes[i].push_back(gene);
        }
    }

    return chromosomes;
}
