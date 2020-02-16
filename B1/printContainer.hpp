#ifndef LABS_LABS_CONTAINER_OUTPUT_HPP
#define LABS_LABS_CONTAINER_OUTPUT_HPP

#include <iostream>

template<typename Container>
void printContainer(const Container &container, const char *delimiter = " ", const char *end = "\n")
{
  for (auto i = container.begin(); i != container.end(); i++)
  {
    std::cout << *i << delimiter;
  }

  std::cout << end;
}

#endif
