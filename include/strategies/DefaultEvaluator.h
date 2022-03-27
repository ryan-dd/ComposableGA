#ifndef DEFAULTEVALUATOR_H
#define DEFAULTEVALUATOR_H

#include <entt/entt.hpp>

#include <functional>
#include <vector>

class DefaultEvaluator
{
public:
    struct DefaultEvaluatorInputs
    {
        std::function<double(std::vector<entt::entity>&)> objectiveFunction;
        int numberOfIterations = 0;
        int numChromosomes = 0;
    };

    DefaultEvaluator(DefaultEvaluatorInputs evaluatorInputs);
    bool continueIterating(std::vector<std::vector<entt::entity>>& chromosomes);
    std::vector<double> getScores(std::vector<std::vector<entt::entity>> input);
    int getResult();

private:
    DefaultEvaluatorInputs inputs;
    int currIterations = 0;
    std::vector<double> scores;
};

#endif // DEFAULTEVALUATOR_H
