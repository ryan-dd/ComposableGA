#ifndef EVY_INDEXABLE_RANGE_H
#define EVY_INDEXABLE_RANGE_H

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
