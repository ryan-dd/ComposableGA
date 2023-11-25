#ifndef EVY_MUTATION_HPP
#define EVY_MUTATION_HPP

namespace evy
{

template<typename MutationStrategy>
class Mutation
{
public:
  MutationStrategy mutationStrategy;

  template<std::ranges::range ChromosomeContainer>
  requires std::invocable<MutationStrategy, 
           std::ranges::range_value_t<ChromosomeContainer>&>
  constexpr void operator()(ChromosomeContainer& chromosomes)
  {
    for(auto& chromosome: chromosomes)
    {
      mutationStrategy(chromosome);
    }
  }
};

}

#endif
