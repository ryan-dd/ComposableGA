#include "evy/evaluation/Evaluate.h"
#include "evy/Pipeline.h"
#include "evy/evaluation/Evaluate.h"
#include "evy/mutation/Mutation.h"
#include "evy/mutation/strategy/IndependentMutation.h"
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
  constexpr double a{1.0};
  constexpr double b{100.0};
  // f(x, y) = (a - x)^2 + b(y-x)^2
  // With normal function the goal is to minimize it, but since selection maximizes by default, multiply function by -1.
  return -(std::pow((a - chromosome.x), 2) + b*std::pow((chromosome.y - std::pow(chromosome.x, 2)), 2));
}

}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  // Initialize mutation strategy
  using MutatorFunctionType = std::function<void(Rosenbrock::ChromosomeType&)>;

  // One mutate function per parameter, index 0 for "x" and index 1 for "y"
  constexpr auto min = -10.0;
  constexpr auto max = 10.0;
  const std::array<MutatorFunctionType, 2> mutateFunctions
  {
    evy::MutateNumeric<0, double>(min, max),
    evy::MutateNumeric<1, double>(min, max)
  };

  auto mutationStrategy = evy::IndependentMutation(mutateFunctions);

  // Initialize crossover strategy
  auto crossoverStrategy = evy::TwoPointCrossover<Rosenbrock::ChromosomeType>{};

  // Initialize chromosomes
  constexpr auto numChromosomes{10};

  using ChromosomeContainer = std::array<Rosenbrock::ChromosomeType, numChromosomes>;
  ChromosomeContainer chromosomes{};

  // Initialize chromosomes with the mutation functions
  for(auto& chromosome: chromosomes)
  {
    mutationStrategy(chromosome, 0);
    mutationStrategy(chromosome, 1);
  }

  constexpr auto numIterations{1};
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

  // Get the best chromosome and print out info about it.
  evy::Evaluate(scores, Rosenbrock::objFunction)(chromosomes);

  auto bestChromosomeIndex{std::ranges::distance(
      std::ranges::begin(scores),
      std::ranges::max_element(scores))};
  auto bestChromosome = chromosomes[static_cast<std::size_t>(bestChromosomeIndex)];

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
