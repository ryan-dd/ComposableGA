#include "DefaultGA.h"
#include "Parameter.h"

#include <entt/entt.hpp>

#include <functional>
#include <random>
#include <vector>
#include <iostream>

int main()
{
    try
    {
        entt::registry registry{};

        // Create a function to initialize and mutate parameters of type double 
        std::mt19937 numberGenerator(std::random_device{}());
        constexpr double minMax {100};
        std::uniform_real_distribution<> doubleDist(-minMax, minMax);
        auto doubleGeneratorFunction = [numberGenerator, doubleDist, &registry](auto entity) mutable
        {
            registry.emplace<double>(entity, doubleDist(numberGenerator));
        };

        // Create function to initialize and mutate parameters of type bool
        std::uniform_real_distribution<> boolDist(0, 1);
        auto boolGeneratorFunction = [numberGenerator, boolDist, &registry](auto entity) mutable
        {
            registry.emplace<bool>(entity, boolDist(numberGenerator));
        };

        // Initialize parameters for objective function
        std::vector<entt::entity> parameters {};
        constexpr int numParamSets {10};

        for (auto i {0}; i < numParamSets; ++i)
        {
            parameters.push_back(addParameter(boolGeneratorFunction, registry));
            parameters.push_back(addParameter(doubleGeneratorFunction, registry));
        }

        // Create the objective function. This scores the chromosome based on its fitness.
        auto objFunction = [&registry](std::vector<entt::entity>& chromosome)
        {
            double score {0.0};
            for (auto i {0}; i < numParamSets; ++i)
            {
                // Setting the bool to true "activates" the double next to it and adds it to the score
                if (registry.get<bool>(chromosome[2*i]))
                {
                    score += registry.get<double>(chromosome[2*i+1]);
                }
            }

            return score;
        };

        // Configure GA
        auto ga {configureDefaultGA({
            .numIterations = 100,
            .numChromosomes = 1000,
            .k_numberTournamentSelection = 5,
            .mutationProbability = 0.08,
            .crossoverProbability = 1.05,
            .objectiveFunction = objFunction,
            .parameters = parameters
        }, registry)};
        
        auto bestChromosome {ga.runGA()};

        std::cout << "Parameters: bool, double\n";

        for (auto i {0}; i < numParamSets; ++i)
        {
            std::cout << registry.get<bool>(bestChromosome.at(2*i)) << ", ";
            std::cout << registry.get<double>(bestChromosome.at(2*i+1)) << "\n";
        }

        std::cout << "Ideal Score: " << numParamSets*minMax << '\n';
        std::cout << "Score: " << objFunction(bestChromosome);
    }
    catch(const std::exception& e)
    {
      std::cerr << "Error occurred: " << e.what() << '\n';
    }
    catch(...)
    {
      std::cerr << "Unknown error occurred\n";


    }

        return 0;
}
