#ifndef EVY_INDEXABLE_RANGE_HPP
#define EVY_INDEXABLE_RANGE_HPP

namespace evy
{

template<typename Container>
concept IndexableRange = requires (Container a)
{
  requires std::ranges::range<Container>;
  a[0];
};

}

#endif
