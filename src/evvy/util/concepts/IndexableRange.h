#ifndef EVVY_INDEXABLE_RANGE_H
#define EVVY_INDEXABLE_RANGE_H

namespace evvy
{

template<typename Container>
concept IndexableRange = requires (Container a)
{
  requires std::ranges::range<Container>;
  a[0];
};

}

#endif
