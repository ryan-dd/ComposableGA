#include "DefaultEvaluator.h"

DefaultEvaluator::DefaultEvaluator(DefaultEvaluatorInputs evaluatorInputs): 
    inputs {std::move(evaluatorInputs)}
{
    scores.resize(inputs.numChromosomes, 0);
}

bool DefaultEvaluator::continueIterating(std::vector<std::vector<entt::entity>>& chromosomes)
{
    for (auto i {0U}; i < chromosomes.size(); ++i)
    {
        scores[i] = inputs.objectiveFunction(chromosomes[i]);
    }

    bestChromosome = chromosomes[std::distance(
        scores.begin(), 
        std::max_element(scores.begin(), scores.end())
    )];

    return currIterations++ < inputs.numberOfIterations;
}

const std::vector<double>& DefaultEvaluator::getScores() const
{
    return scores;
}

std::vector<entt::entity> DefaultEvaluator::getResult() const
{
    return bestChromosome;
}
