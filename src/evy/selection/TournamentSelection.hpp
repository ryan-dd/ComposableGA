#ifndef EVY_TOURNAMENT_SELECTION_HPP
#define EVY_TOURNAMENT_SELECTION_HPP

#include "evy/rng/FastIndexRng.hpp"
#include "evy/util/concepts/IndexableRange.hpp"

#include <limits>
#include <array>
#include <ranges>
#include <cassert>

namespace evy
{

template<IndexableRange ScoreContainer, std::invocable IndexRng = FastIndexRng>
requires std::totally_ordered<std::ranges::range_value_t<ScoreContainer>>
class SelectWithTournament
{
private:
  std::reference_wrapper<const ScoreContainer> scoresRef;
  std::size_t tournamentSize;
  using ScoreType = std::ranges::range_value_t<ScoreContainer>;
  using IndexType = std::size_t;
public:
  SelectWithTournament(const ScoreContainer& scores, std::size_t tournamentSize): 
    scoresRef(scores),
    tournamentSize(tournamentSize)
  {
  }

  template<IndexableRange ChromosomeContainer>
  void operator()(ChromosomeContainer& chromosomes)
  {
    auto& scores{ scoresRef.get() };
    assert(chromosomes.size() == scores.size());

    auto oldChromosomes = chromosomes;

    IndexRng rng{static_cast<std::uint32_t>(chromosomes.size() - 1)};
    for(auto& chromosome: chromosomes)
    {
      ScoreType max_score{std::numeric_limits<ScoreType>::lowest()};
      IndexType winnerIndex{0};
      for (std::size_t i{0}; i < tournamentSize; ++i)
      {
        auto scoreIndex{rng()};
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
