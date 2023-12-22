#include "evy/evaluation/Evaluate.hpp"
#include "evy/Pipeline.hpp"
#include "evy/evaluation/Evaluate.hpp"
#include "evy/mutation/Mutation.hpp"
#include "evy/mutation/strategy/IndependentMutation.hpp"
#include "evy/mutation/MutatorFunctions.hpp"
#include "evy/crossover/Crossover.hpp"
#include "evy/crossover/strategies/TwoPointCrossover.hpp"
#include "evy/selection/TournamentSelection.hpp"
#include "evy/stop_condition/StopAfter.hpp"
#include "evy/util/ConstantProbability.hpp"

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <tuple>
#include <utility>

// Define the chromosome type and the objective function in a separate namespace for clarity
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

auto getMutateStrategy(double mutateProbability)
{
  constexpr auto min{-10.0};
  constexpr auto max{10.0};

  // One mutate function per parameter, index 0 for "x" and index 1 for "y"
  std::array mutateFunctions
  {
    evy::MutateNumeric<double>(min, max),
    evy::MutateNumeric<double>(min, max)
  };

  return evy::IndependentMutation(mutateFunctions, evy::ConstantProbability(mutateProbability));
}

void initializeChromosome(std::ranges::range auto& chromosomes)
{
  constexpr auto min{-10.0};
  constexpr auto max{10.0};
  evy::MutateNumeric<double> mutator(min, max);
  for(auto& chromosome: chromosomes)
  {
    mutator(chromosome.x);
    mutator(chromosome.y);
  }
}

int main()
{
  auto start{std::chrono::high_resolution_clock::now()};

  // Initialize chromosomes
  constexpr auto numChromosomes{10000};
  auto chromosomes = std::array<Rosenbrock::ChromosomeType, numChromosomes>{};
  initializeChromosome(chromosomes);

  auto scores = std::array<Rosenbrock::ScoreType, numChromosomes>{};

  constexpr auto numIterations{100};
  constexpr auto tournamentSize{30};
  constexpr auto crossoverProbability{0.4};
  constexpr auto mutateProbability{0.2};

  evy::Pipeline::run(
      chromosomes, 
      evy::StopAfter(numIterations),
      // Pipeline start
      evy::Evaluate(scores, Rosenbrock::objFunction),
      evy::SelectWithTournament(scores, tournamentSize),
      evy::Crossover(
        evy::ConstantProbability(crossoverProbability), 
        evy::TwoPointCrossover<Rosenbrock::ChromosomeType>{}),
      evy::Mutation(getMutateStrategy(mutateProbability))
      // Pipeline end
  );

  // Get the best chromosome and print out info about it.
  evy::Evaluate(scores, Rosenbrock::objFunction)(chromosomes);

  auto bestChromosomeIndex{std::ranges::distance(
      std::ranges::begin(scores),
      std::ranges::max_element(scores))};
  auto bestChromosome{chromosomes[static_cast<std::size_t>(bestChromosomeIndex)]};

  auto end{std::chrono::high_resolution_clock::now()};
  auto millisecondsElapsed{std::chrono::duration_cast<std::chrono::milliseconds>(end - start)};

  std::cout << "Time elapsed:\n ";
  std::cout << millisecondsElapsed.count() << "ms\n";

  std::cout << "Ideal:\n Param 1: 1.0\n Param 2: 1.0\n Score: 0\n";
  std::cout << "Actual:\n";
  std::cout << " Param 1: " << bestChromosome.x << ',' << '\n';
  std::cout << " Param 2: " << bestChromosome.y << ',' << '\n';
  std::cout << " Score: " << Rosenbrock::objFunction(bestChromosome) << '\n';
}
