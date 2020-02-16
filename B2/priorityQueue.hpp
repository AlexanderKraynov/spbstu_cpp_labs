#ifndef LABS_LABS_PRIORITY_QUEUE_HPP
#define LABS_LABS_PRIORITY_QUEUE_HPP

#include <list>
#include <iostream>
#include <stdexcept>

template<typename T>
class PriorityQueue
{
public:
  enum class ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  bool put(const T &, ElementPriority);
  template<typename HandlerType>
  bool handleFront(HandlerType);
  void accelerate();
  bool empty() const;
  int size() const;

private:
  std::list<T> low;
  std::list<T> normal;
  std::list<T> high;
};

template<typename T>
bool PriorityQueue<T>::put(const T &element, ElementPriority priority)
{
  switch (priority)
  {
    case ElementPriority::HIGH:
    {
      high.push_back(element);
      return true;
    }
    case ElementPriority::NORMAL:
    {
      normal.push_back(element);
      return true;
    }
    case ElementPriority::LOW:
    {
      low.push_back(element);
      return true;
    }
    default :
      return false;
  }
}

template<typename T>
template<typename HandlerType>
bool PriorityQueue<T>::handleFront(HandlerType handler)
{
  if (!high.empty())
  {
    handler(high.front());
    high.pop_front();
    return true;
  }
  if (!normal.empty())
  {
    handler(normal.front());
    normal.pop_front();
    return true;
  }
  if (!low.empty())
  {
    handler(low.front());
    low.pop_front();
    return true;
  }
  return false;
}

template<typename T>
void PriorityQueue<T>::accelerate()
{
  high.splice(high.end(), low);
}

template<typename T>
bool PriorityQueue<T>::empty() const
{
  return (low.empty() && normal.empty() && high.empty());
}

template<typename T>
int PriorityQueue<T>::size() const
{
  return (low.size() + normal.size() + high.size());
}

#endif
