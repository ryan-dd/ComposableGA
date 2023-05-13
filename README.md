# Evy

A header-only, composable evolutionary algorithm toolkit taking advantage of the latest C++20 features. See `examples` for more details and documentation.

Out of the box, supports running genetic algorithm with custom aggregate types and objective functions. Heavily depends on concepts and templates to avoid any inheritance boilerplate code and allow for customization flexibility.

# Dependencies

Depends on header-only [__boost::pfr__](https://github.com/boostorg/pfr) (aka magic\_get) to facilitate accessing each member variable of a aggregate by numbered index (hopefully this will be in the standard library eventually, see [P2141](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2141r0.html))

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
  // f(x, y) = -(a - x)^2 + b(y-x)^2
  // With normal function the goal is to minimize it, but since selection maximizes by default, multiply function by -1.
  return -(std::pow((a - chromosome.x), 2) + b*std::pow((chromosome.y - std::pow(chromosome.x, 2)), 2));
}

}
```

Notice how no inheritance of base classes are required, just simply declaring and using types and functions.

We can then define a basic mutation strategy for our chromosomes where we define a mutation function for the `ChromosomeType` members `x` and `y`.
We use the IndependentMutation functor, which takes in the functions as arguments and has a call operator that matches the interface below:

```C++
void customMutateStrategy(ChromosomeType& chromosome, std::size_t index)
```

Usage:


```C++
constexpr auto min = -10.0;
constexpr auto max = 10.0;
// Slight performance hit with type erasure, but custom mutator functions could be substituted instead
using MutatorFunctionType = std::function<void(ChromosomeType&)>;

// One mutate function per parameter, index 0 for "x" and index 1 for "y"
const std::array<MutatorFunctionType, 2> mutateFunctions
{
  // The utility function evy::MutateNumeric generates random numbers with a uniform distribution for integer or floating point types. 
  evy::MutateNumeric<0, double>(min, max),
  evy::MutateNumeric<1, double>(min, max)
};

auto mutationStrategy = evy::IndependentMutation(mutateFunctions);
```

The crossover strategy should match the interface of:

```C++
void customCrossover(ChromosomeType& c1, ChromosomeType& c2);
```

In this example, we use the two point crossover strategy provided by evy.

```C++
auto crossoverStrategy = evy::TwoPointCrossover<Rosenbrock::ChromosomeType>{}; ```
```

We can then define and initialize the initial chromosome population

```C++
constexpr auto numChromosomes{10000};

using ChromosomeContainer = std::array<Rosenbrock::ChromosomeType, numChromosomes>;
ChromosomeContainer chromosomes{};

// Initialize chromosomes with the mutation functions
for(auto& chromosome: chromosomes)
{
  mutationStrategy(chromosome, 0);
  mutationStrategy(chromosome, 1);
}
```

We can then define the parameters necessary and run the genetic algorithm, with the steps being: Evaluate, selection, crossover, and mutation.

```C++
constexpr auto numIterations{10000};
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

Finally, we can get the best chromosome with a helper method and print out the objective function result.

```C++
evy::Evaluate(scores, Rosenbrock::objFunction)(chromosomes);

auto bestChromosomeIndex{std::ranges::distance(
    std::ranges::begin(scores),
    std::ranges::max_element(scores))};
auto bestChromosome = chromosomes[static_cast<std::size_t>(bestChromosomeIndex)];

std::cout << " Param 1: " << bestChromosome.x << ',' << '\n';
std::cout << " Param 2: " << bestChromosome.y << ',' << '\n';
std::cout << " Score: " << Rosenbrock::objFunction(bestChromosome) << '\n';
```
