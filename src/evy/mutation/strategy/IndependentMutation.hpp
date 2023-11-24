#ifndef EVY_BASIC_MUTATION_H
#define EVY_BASIC_MUTATION_H

namespace evy
{


template<typename IndexableFunctions, typename Arg>
concept IndexableFunctionsCallableBy = requires (IndexableFunctions functions, Arg arg)
{
  functions[0](arg);
};

template<typename MutateFunctions>
class IndependentMutation
{
public:
  explicit IndependentMutation(MutateFunctions mutateFunctions)
    : mutateFunctions(mutateFunctions)
  {
  }

  template<typename ChromosomeType>
    requires IndexableFunctionsCallableBy<MutateFunctions, ChromosomeType>
    void operator()(ChromosomeType& chromosome, std::size_t index)
    {
      mutateFunctions[index](chromosome);
    }

private:
  MutateFunctions mutateFunctions;

};

}

#endif
