#include "evvy/Pipeline.h"
#include "evvy/evaluation/Evaluate.h"
#include "evvy/mutation/Mutation.h"
#include "evvy/mutation/MutatorFunctions.h"
#include "evvy/crossover/Crossover.h"
#include "evvy/crossover/strategies/TwoPointCrossover.h"
#include "evvy/selection/TournamentSelection.h"
#include "evvy/stop_condition/StopAfter.h"
#include "evvy/util/ConstantProbability.h"

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

constexpr auto min = -10.0;
constexpr auto max = 10.0;
using MutatorFunctionType = std::function<void(ChromosomeType&)>;

// One mutate function per parameter, index 0 for "x" and index 1 for "y"
const std::array<MutatorFunctionType, 2> mutateFunctions
{
  evvy::MutateNumeric<0, double>(min, max),
  evvy::MutateNumeric<1, double>(min, max)
};

}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();

  constexpr auto numChromosomes{10000};
  constexpr auto numIterations{100};
  constexpr auto tournamentSize{5};
  constexpr auto mutateProbability{0.8};
  constexpr auto crossoverProbability{0.4};

  using ChromosomeContainer = std::array<Rosenbrock::ChromosomeType, numChromosomes>;
  using ScoreContainer = std::array<Rosenbrock::ScoreType, numChromosomes>;

  ChromosomeContainer chromosomes{};
  ScoreContainer scores{};

  // Initialize chromosomes with the mutation functions
  for(auto& chromosome: chromosomes)
  {
    for(const auto& mutateFunction: Rosenbrock::mutateFunctions)
    {
      mutateFunction(chromosome);
    }
  }

  // Set up crossover
  auto crossoverStrategy = evvy::TwoPointCrossover<Rosenbrock::ChromosomeType>{};
  auto crossover = evvy::Crossover(evvy::ConstantProbability(crossoverProbability), crossoverStrategy);

  // Set up mutation
  auto mutationStrategy = // Calls the correct mutation function for the index selected
    [mutateFunctions = Rosenbrock::mutateFunctions](Rosenbrock::ChromosomeType& chromosome, std::size_t index)
    {
      mutateFunctions[index](chromosome);
    };

  auto mutation = evvy::Mutation(
      evvy::ConstantProbability(mutateProbability), 
      mutationStrategy,
      evvy::compileTimeSize<Rosenbrock::ChromosomeType>());

  // Run Genetic Algorithm
  evvy::Pipeline::run(
      chromosomes, 
      evvy::StopAfter(numIterations),
      // Pipeline start
      evvy::Evaluate(scores, Rosenbrock::objFunction),
      evvy::SelectWithTournament(scores, tournamentSize),
      crossover,
      mutation
      // Pipeline end
  );

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
