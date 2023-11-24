#ifndef EVY_BASIC_MUTATION_H
#define EVY_BASIC_MUTATION_H

namespace evy
{

template<typename MutateFunctions>
class IndependentMutation
{
public:
  explicit IndependentMutation(MutateFunctions mutateFunctions)
    : mutateFunctions(mutateFunctions)
  {
  }

  template<typename ChromosomeType>
    requires requires (MutateFunctions mutateFunctions, ChromosomeType chromosome)
    {
      mutateFunctions[0](chromosome);
    }
  void operator()(ChromosomeType& chromosome, std::size_t index)
  {
    mutateFunctions[index](chromosome);
  }

private:
  MutateFunctions mutateFunctions;

};

}

#endif
