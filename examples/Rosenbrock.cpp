#include "evy/Pipeline.h"
#include "evy/evaluation/Evaluate.h"
#include "evy/mutation/Mutation.h"
#include "evy/mutation/MutatorFunctions.h"
#include "evy/crossover/Crossover.h"
#include "evy/crossover/strategies/TwoPointCrossover.h"
#include "evy/selection/TournamentSelection.h"
#include "evy/stop_condition/StopAfter.h"
#include "evy/util/ConstantProbability.h"

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <tuple>
#include <utility>

namespace Rosenbrock
{

struct ChromosomeType
{
  double x;
  double y;
};

using ScoreType = double;

ScoreType objFunction(const ChromosomeType& chromosome)
{
  // Rosenbrock function - https://en.wikipedia.org/wiki/Rosenbrock_function 
  constexpr double a {1.0};
  constexpr double b {100.0};
  return -(std::pow((a - chromosome.x), 2) + b*std::pow((chromosome.y - std::pow(chromosome.x, 2)), 2));
}

}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // Initialize mutation strategy
  constexpr auto min = -10.0;
  constexpr auto max = 10.0;
  using MutatorFunctionType = std::function<void(Rosenbrock::ChromosomeType&)>;

  // One mutate function per parameter, index 0 for "x" and index 1 for "y"
  const std::array<MutatorFunctionType, 2> mutateFunctions
  {
    evy::MutateNumeric<0, double>(min, max),
    evy::MutateNumeric<1, double>(min, max)
  };

  // Make class to encapsulate this.
  auto mutationStrategy = // Calls the correct mutation function for the index selected
    [mutateFunctions](Rosenbrock::ChromosomeType& chromosome, std::size_t index)
    {
      mutateFunctions[index](chromosome);
    };

  // Initialize crossover strategy
  auto crossoverStrategy = evy::TwoPointCrossover<Rosenbrock::ChromosomeType>{};

  // Initialize chromosomes
  constexpr auto numChromosomes{10000};
  using ChromosomeContainer = std::array<Rosenbrock::ChromosomeType, numChromosomes>;
  ChromosomeContainer chromosomes{};

  // Initialize chromosomes with the mutation functions
  for(auto& chromosome: chromosomes)
  {
    for(const auto& mutateFunction: mutateFunctions)
    {
      mutateFunction(chromosome);
    }
  }

  constexpr auto numIterations{100};
  constexpr auto tournamentSize{5};
  constexpr auto mutateProbability{0.8};
  constexpr auto crossoverProbability{0.4};

  using ScoreContainer = std::array<Rosenbrock::ScoreType, numChromosomes>;
  ScoreContainer scores{};

  evy::Pipeline::run(
      chromosomes, 
      evy::StopAfter(numIterations),
      // Pipeline start
      evy::Evaluate(scores, Rosenbrock::objFunction),
      evy::SelectWithTournament(scores, tournamentSize),
      evy::Crossover(
        evy::ConstantProbability(crossoverProbability), 
        crossoverStrategy),
      evy::Mutation(
        evy::ConstantProbability(mutateProbability), 
        mutationStrategy,
        evy::compileTimeSize<Rosenbrock::ChromosomeType>())
      // Pipeline end
  );

  // Make function getBestChromosome(chromosomes, objfunction);
  std::ranges::transform(
      chromosomes, 
      std::ranges::begin(scores), 
      Rosenbrock::objFunction);

  auto bestChromosomeIndex{static_cast<std::size_t>(std::ranges::distance(
      std::ranges::begin(scores),
      std::ranges::max_element(scores))
      )};
  auto bestChromosome = chromosomes[bestChromosomeIndex];

  auto end = std::chrono::high_resolution_clock::now();
  auto millisecondsElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "Time elapsed:\n ";
  std::cout << millisecondsElapsed.count() << "ms\n";

  std::cout << "Ideal:\n Param 1: 1.0\n Param 2: 1.0\n Score: 0\n";
  std::cout << "Actual:\n";
  std::cout << " Param 1: " << bestChromosome.x << ',' << '\n';
  std::cout << " Param 2: " << bestChromosome.y << ',' << '\n';
  std::cout << " Score: " << Rosenbrock::objFunction(bestChromosome) << '\n';
}
