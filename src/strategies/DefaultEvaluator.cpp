#include "DefaultEvaluator.h"

DefaultEvaluator::DefaultEvaluator(DefaultEvaluatorInputs evaluatorInputs): 
        inputs(evaluatorInputs)
{
    scores.resize(inputs.numChromosomes, 0);
}

bool DefaultEvaluator::continueIterating(std::vector<std::vector<entt::entity>>& chromosomes)
{
    return currIterations++ < inputs.numberOfIterations;
}

std::vector<double> DefaultEvaluator::getScores(std::vector<std::vector<entt::entity>> input)
{
    for(auto i = 0u; i < input.size(); ++i)
    {
        scores.at(i) = inputs.objectiveFunction(input.at(i));
    }

    return scores;
}

int DefaultEvaluator::getResult(){
    return std::distance(
        scores.begin(), 
        std::max_element(scores.begin(), scores.end())
    );
}