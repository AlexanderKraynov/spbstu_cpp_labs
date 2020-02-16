#ifndef LABS_LABS_FACTORIALCONTAINER_HPP
#define LABS_LABS_FACTORIALCONTAINER_HPP

#include <cstdlib>
#include <iterator>
#include <limits>

class FactorialContainer
{
public:
  class iterator : public std::iterator<std::bidirectional_iterator_tag, unsigned long long, std::ptrdiff_t, int, int>
  {
  public:
    iterator &operator++();
    iterator &operator--();
    iterator operator++(int);
    iterator operator--(int);
    value_type operator*();
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    static constexpr int getMaxIndex();
  private:
    iterator(int index, int value, int maxIndex);
    int index;
    value_type value;
    int maxIndex;

    friend class FactorialContainer;
  };

  using value_type = unsigned long long;
  using const_iterator = iterator;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using difference_type = std::ptrdiff_t;

  explicit FactorialContainer(int size);

  iterator begin() const;
  iterator end() const;

  const_iterator cbegin() const;
  const_iterator cend() const;

  reverse_iterator rbegin() const;
  reverse_iterator rend() const;

  bool empty() const;
private:
  value_type value;
  int maxIndex;
  int size;
};

#endif
