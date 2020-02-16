#include "FactorialContainer.hpp"

constexpr int FactorialContainer::iterator::getMaxIndex()
{
  int n = 0;
  value_type fact = 1;
  while (fact < (std::numeric_limits<value_type>::max() / ++n))
  {
    fact *= n;
  }
  return n - 2;
}

FactorialContainer::iterator::iterator(int index, int value, int maxIndex) :
  index(index),
  value(value),
  maxIndex(maxIndex)
{
  if (index <= 0)
  {
    throw std::out_of_range("Index must be positive\n");
  }
}

FactorialContainer::iterator &FactorialContainer::iterator::operator++()
{
  if (index >= maxIndex)
  {
    throw std::out_of_range("Index out of range\n");
  }
  index++;
  value = value * index;
  return (*this);
}

FactorialContainer::iterator &FactorialContainer::iterator::operator--()
{
  if (index <= 0)
  {
    throw std::out_of_range("Index must be positive\n");
  }
  value = value / index;
  index--;
  return (*this);
}

FactorialContainer::iterator FactorialContainer::iterator::operator++(int)
{
  iterator tmp(*this);
  this->operator++();
  return --tmp;
}

FactorialContainer::iterator FactorialContainer::iterator::operator--(int)
{
  iterator tmp(*this);
  this->operator--();
  return tmp;
}

FactorialContainer::value_type FactorialContainer::iterator::operator*()
{
  return value;
}

bool FactorialContainer::iterator::operator==(const FactorialContainer::iterator &other) const
{
  return (index == other.index);
}

bool FactorialContainer::iterator::operator!=(const FactorialContainer::iterator &other) const
{
  return !(*this == other);
}

FactorialContainer::iterator FactorialContainer::begin() const
{
  return iterator(1, 1, maxIndex);
}

FactorialContainer::iterator FactorialContainer::end() const
{
  return iterator(size, value, maxIndex);
}

FactorialContainer::const_iterator FactorialContainer::cbegin() const
{
  return const_iterator(1, 1, maxIndex);
}

FactorialContainer::const_iterator FactorialContainer::cend() const
{
  return const_iterator(size - 1, value, maxIndex);
}

FactorialContainer::reverse_iterator FactorialContainer::rbegin() const
{
  return FactorialContainer::reverse_iterator(cend());
}

FactorialContainer::reverse_iterator FactorialContainer::rend() const
{
  return FactorialContainer::reverse_iterator(cbegin());
}


bool FactorialContainer::empty() const
{
  return (size == 0);
}

FactorialContainer::FactorialContainer(int size)
{
  constexpr int tmp = iterator::getMaxIndex();
  maxIndex = tmp;
  if (size > maxIndex)
  {
    throw std::out_of_range("FactorialContainer value is out of range");
  }
  this->size = size;
  value = 1;
  for (int i = 2; i <= size; ++i)
  {
    value = value * i;
  }
}
