#ifndef EVVY_INDEPENDENT_PARAMATER_MUTATION_H
#define EVVY_INDEPENDENT_PARAMATER_MUTATION_H

#include <array>
#include <tuple>
#include <random>

#include <boost/pfr.hpp>

namespace evvy
{

template<typename MutateFunctions>
class MutateIndependentParameters
{
private:
  MutateFunctions& mutateFunctions;
  double mutateProbability;
public:
  MutateIndependentParameters(MutateFunctions& mutateFunctions, double mutateProbability):
    mutateFunctions(mutateFunctions),
    mutateProbability(mutateProbability)
  {}

template<typename ChromosomeContainer>
void operator()(ChromosomeContainer& chromosomes)
{
  constexpr auto numParams{boost::pfr::tuple_size_v<typename ChromosomeContainer::value_type>};
  for(auto& chromosome: chromosomes)
  {
    for(auto j{0}; j < numParams; ++j)
    {
      static auto real_dist{std::uniform_real_distribution<>(0.0, 1.0)};
      static std::mt19937 numberGenerator(std::random_device{}());
      if(real_dist(numberGenerator) < mutateProbability)
      {
        mutateFunctions[j](chromosome);
      }
    }
  }
}

};

}

#endif
