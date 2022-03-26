#ifndef DEFAULTEVALUATOR_H
#define DEFAULTEVALUATOR_H

#include <entt/entt.hpp>

class DefaultEvaluator
{
public:
    struct DefaultEvaluatorInputs
    {
        std::function<double(std::vector<entt::entity>&)> objectiveFunction;
        int numberOfIterations = 0;
        int numChromosomes = 0;
    };

    DefaultEvaluator(DefaultEvaluatorInputs evaluatorInputs): 
        inputs(evaluatorInputs)
    {
        scores.resize(inputs.numChromosomes, 0);
    }
    
    bool continueIterating(std::vector<std::vector<entt::entity>>& chromosomes)
    {
        return currIterations++ < inputs.numberOfIterations;
    }

    std::vector<double> getScores(std::vector<std::vector<entt::entity>> input)
    {
        for(int i = 0; i < input.size(); ++i)
        {
            scores.at(i) = inputs.objectiveFunction(input.at(i));
        }

        return scores;
    };

    int getResult(){
        return std::distance(scores.begin(),std::max_element(scores.begin(), scores.end())); // Max index
    };

private:
    DefaultEvaluatorInputs inputs;
    int currIterations = 0;
    std::vector<double> scores;
};

#endif // DEFAULTEVALUATOR_H
