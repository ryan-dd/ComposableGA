#include "evvy/Pipeline.h"
#include "evvy/evaluation/Evaluate.h"
#include "evvy/mutation/IndependentParameterMutation.h"
#include "evvy/mutation/MutatorFunctions.h"
#include "evvy/crossover/IndependentParameterCrossover.h"
#include "evvy/selection/TournamentSelection.h"
#include "evvy/stop_condition/StopAfter.h"

#include <algorithm>
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
  // Rosenbrock function
  constexpr double a {1.0};
  constexpr double b {100.0};
  return -(std::pow((a - chromosome.x), 2) + b*std::pow((chromosome.y - std::pow(chromosome.x, 2)), 2));
}

constexpr auto min = -10.0;
constexpr auto max = 10.0;
constexpr std::array mutateFunctions
{
  evvy::mutateNumeric<0, ChromosomeType, double, min, max>,
  evvy::mutateNumeric<1, ChromosomeType, double, min, max>
};

}

int main()
{
  constexpr auto numChromosomes{10};
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

  auto stopCondition = evvy::StopAfter(numIterations);

  evvy::Pipeline::run(
      chromosomes, 
      stopCondition,
      // Pipeline start
      evvy::Evaluate(scores, Rosenbrock::objFunction),
      evvy::SelectWithTournament(scores, tournamentSize),
      evvy::MutateIndependentParameters(Rosenbrock::mutateFunctions, mutateProbability),
      evvy::CrossoverIndependentParameters<Rosenbrock::ChromosomeType>(crossoverProbability)
      // Pipeline end
      );

  std::transform(
      chromosomes.cbegin(), chromosomes.cend(), 
      scores.begin(), Rosenbrock::objFunction);

  auto bestChromosome = chromosomes[std::distance(
      scores.begin(), 
      std::max_element(scores.begin(), scores.end())
      )];

  std::cout << "Ideal:\n Param 1: 1.0\n Param 2: 1.0\n Score: 0\n";
  std::cout << "Actual:\n";
  std::cout << " Param 1: " << bestChromosome.x << ',' << '\n';
  std::cout << " Param 2: " << bestChromosome.y << ',' << '\n';
  std::cout << " Score: " << Rosenbrock::objFunction(bestChromosome) << '\n';
}
