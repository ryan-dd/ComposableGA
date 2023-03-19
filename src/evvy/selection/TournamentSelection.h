#ifndef EVVY_TOURNAMENT_SELECTION_H
#define EVVY_TOURNAMENT_SELECTION_H

#include <limits>
#include <random>
#include <array>
#include <ranges>
#include <cassert>

namespace evvy
{

template<typename ScoreContainer>
class SelectWithTournament
{
private:
  const ScoreContainer& scores;
  std::size_t tournamentSize;
  using ScoreType = typename ScoreContainer::value_type;
  using IndexType = std::size_t;
public:
  SelectWithTournament(const ScoreContainer& scores, std::size_t tournamentSize): 
    scores(scores),
    tournamentSize(tournamentSize)
  {
  }

  template<typename ChromosomeContainer>
  void operator()(ChromosomeContainer& chromosomes)
  {
    assert(chromosomes.size() == scores.size());
    static std::mt19937_64 random_engine{std::random_device{}()};

    auto oldChromosomes = chromosomes;

    std::uniform_int_distribution<> intDistributionForChromosome(0, chromosomes.size()-1);
    for(auto& chromosome: chromosomes)
    {
      ScoreType max_score{std::numeric_limits<ScoreType>::lowest()};
      IndexType winnerIndex{0};
      for (auto i{0}; i < tournamentSize; ++i)
      {
        auto scoreIndex{intDistributionForChromosome(random_engine)};
        if(scores[scoreIndex] > max_score)
        {
          max_score = scores[scoreIndex];
          winnerIndex = scoreIndex;
        }
      }
      chromosome = oldChromosomes[winnerIndex];
    }
  }
};

}
#endif
