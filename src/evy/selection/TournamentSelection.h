#ifndef EVY_TOURNAMENT_SELECTION_H
#define EVY_TOURNAMENT_SELECTION_H

#include "evy/rng/FastIndexRng.h"
#include "evy/util/concepts/IndexableRange.h"

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
  const ScoreContainer& scores;
  std::size_t tournamentSize;
  using ScoreType = std::ranges::range_value_t<ScoreContainer>;
  using IndexType = std::size_t;
public:
  SelectWithTournament(const ScoreContainer& scores, std::size_t tournamentSize): 
    scores(scores),
    tournamentSize(tournamentSize)
  {
  }

  template<IndexableRange ChromosomeContainer>
  void operator()(ChromosomeContainer& chromosomes)
  {
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
