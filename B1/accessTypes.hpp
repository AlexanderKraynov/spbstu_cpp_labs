#ifndef LABS_ACCESS_TYPES_HPP
#define LABS_ACCESS_TYPES_HPP

#include <iterator>

template<typename Container>
struct BracketAccess
{
  typedef typename Container::size_type ContainerIterator;
  typedef typename Container::reference ContainerReference;

  static ContainerIterator begin(const Container &)
  {
    return 0;
  }

  static ContainerIterator end(const Container &container)
  {
    return container.size();
  }

  static ContainerReference get(Container &container, ContainerIterator index)
  {
    return container[index];
  }
};

template<typename Container>
struct AtAccess
{
  typedef typename Container::size_type ContainerIterator;
  typedef typename Container::reference ContainerReference;

  static ContainerIterator begin(const Container &)
  {
    return 0;
  }

  static ContainerIterator end(const Container &container)
  {
    return container.size();
  }

  static ContainerReference get(Container &container, ContainerIterator index)
  {
    return container.at(index);
  }
};

template<typename Container>
struct IteratorAccess
{
  typedef typename Container::iterator ContainerIterator;
  typedef typename Container::reference ContainerReference;

  static ContainerIterator begin(Container &container)
  {
    return container.begin();
  }

  static ContainerIterator end(Container &container)
  {
    return container.end();
  }

  static ContainerReference get(Container &, ContainerIterator iterator)
  {
    return *iterator;
  }
};

#endif
