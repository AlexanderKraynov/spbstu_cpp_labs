#ifndef LABS_HEAPSORT_HPP
#define LABS_HEAPSORT_HPP

#include <functional>
#include <algorithm>
#include <stdexcept>
#include "accessTypes.hpp"

template<typename Element>
std::function<bool(Element, Element)> getComparator(const std::string &input)
{
  if (input == "ascending")
  {
    return std::less<>{};
  }
  if (input == "descending")
  {
    return std::greater<>{};
  }
  throw std::invalid_argument{"ascending|descending usage only"};
}


template<template<class> class AccessType = IteratorAccess, typename Container, class ComparatorType>
void sort(Container &container, ComparatorType comparator)
{
  using AccessTypeInitialized = AccessType<Container>;
  auto begin = AccessType<Container>::begin(container);
  auto end = AccessType<Container>::end(container);
  for (auto i = begin; i != end; i++)
  {
    for (auto j = i; j != end; j++)
    {
      if (comparator(AccessType<Container>::get(container, j), AccessTypeInitialized::get(container, i)))
      {
        std::swap(AccessType<Container>::get(container, j), AccessTypeInitialized::get(container, i));
      }
    }
  }
}

#endif
