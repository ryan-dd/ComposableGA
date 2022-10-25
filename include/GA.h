#ifndef GA_H
#define GA_H

template<
    typename InitialSolutionGenerator,
    typename Evaluator,
    typename ParentSelector,
    typename Crossover,
    typename Mutator
    >
class GA
{
public:
    GA(const InitialSolutionGenerator& generator,
        const Evaluator& evaluator,
        const ParentSelector& selector,
        const Crossover& crossover,
        const Mutator& mutator):
    generator(generator),
    evaluator(evaluator),
    selector(selector),
    crossover(crossover),
    mutator(mutator){}

    auto runGA()
    {
        auto currentPopulation = generator.generate();
        
        while (evaluator.continueIterating(currentPopulation))
        {
            selector.selectParents(currentPopulation, evaluator.getScores());
            crossover.crossover(currentPopulation);
            mutator.mutate(currentPopulation);
        }

        return evaluator.getResult();
    }

private:
    InitialSolutionGenerator generator;
    Evaluator evaluator;
    ParentSelector selector;
    Crossover crossover;
    Mutator mutator;
};

#endif // GA_H
