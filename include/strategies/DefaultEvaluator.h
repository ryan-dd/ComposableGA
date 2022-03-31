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

    explicit DefaultEvaluator(const DefaultEvaluatorInputs& evaluatorInputs);
    bool continueIterating(std::vector<std::vector<entt::entity>>& chromosomes);
    const std::vector<double>& getScores() const;
    std::vector<entt::entity> getResult() const;

private:
    DefaultEvaluatorInputs inputs;
    int currIterations = 0;
    std::vector<double> scores;
    std::vector<entt::entity> bestChromosome;
};

#endif // DEFAULTEVALUATOR_H
