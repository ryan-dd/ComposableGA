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
        std::function<double(std::vector<entt::entity>&)> objectiveFunction{};
        int numberOfIterations{};
        int numChromosomes{};
    };

    explicit DefaultEvaluator(DefaultEvaluatorInputs evaluatorInputs);
    bool continueIterating(std::vector<std::vector<entt::entity>>& chromosomes);
    const std::vector<double>& getScores() const;
    std::vector<entt::entity> getResult() const;

private:
    const DefaultEvaluatorInputs inputs{};
    int currIterations{0};
    std::vector<double> scores{};
    std::vector<entt::entity> bestChromosome{};
};

#endif // DEFAULTEVALUATOR_H
