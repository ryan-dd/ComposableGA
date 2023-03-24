# Evy

A header-only, composable evolutionary algorithm toolkit taking advantage of the latest C++20 features. See `examples` for more details and documentation.

Out of the box, supports running genetic algorithm with custom POD types and objective functions. Heavily depends on concepts and templates to avoid any inheritance and associated runtime penalties.

# Dependencies

Depends on header-only __boost::pfr__ to facilitate accessing each member variable of a POD struct by numbered index (hopefully this will be in the standard library eventually, see [P2141](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2141r0.html))

# Genetic Algorithm Tutorial

Using a Rosenbrock function as an example, the objective function would be defined as follows:

```C++
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
```

Notice how no inheritance of base classes are requires, just simply declaring and using types and functions.

We can then define a mutation strategy for our chromosomes matching the signature of `void myMutateStrategy(ChromosomeType& chromosome, std::size_t index)`.

```C++

constexpr auto min = -10.0;
constexpr auto max = 10.0;
using MutatorFunctionType = std::function<void(ChromosomeType&)>;

// One mutate function per parameter, index 0 for "x" and index 1 for "y"
const std::array<MutatorFunctionType, 2> mutateFunctions
{
  evy::MutateNumeric<0, double>(min, max),
  evy::MutateNumeric<1, double>(min, max)
};

auto mutationStrategy = // Calls the correct mutation function for the index selected
  [mutateFunctions = Rosenbrock::mutateFunctions](Rosenbrock::ChromosomeType& chromosome, std::size_t index)
  {
    mutateFunctions[index](chromosome);
  };
```

The utility function `evy::MutateNumeric` is used to as a random number generator with a uniform distribution for integer and floating point types. 
Note that passing the whole chromosome in the function along with the index allows for flexibility in the mutation strategy for problem domains such as the travelling salesman problem (TSP) that require some form of chromosome repair after the mutation.

The crossover strategy is simpler to specify:

```C++
auto crossoverStrategy = evy::TwoPointCrossover<Rosenbrock::ChromosomeType>{};
```

We can then define and initialize the initial chromosome population

```C++
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
```

Finally, we can define the parameters necessary and run the genetic algorithm, with the steps being: Evaluate, selection, crossover, and mutation.

```C++
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
```

We can get the best 

