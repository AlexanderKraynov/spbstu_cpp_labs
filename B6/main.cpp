#include <iterator>
#include <iostream>
#include <algorithm>
#include "Statistics.hpp"

int main(int argc, char *[])
{
  if (argc != 1)
  {
    std::cerr << "0 arguments expected";
    return 1;
  }
  Statistics stat = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), Statistics());
  if (!std::cin.eof())
  {
    std::cerr << "Input failed";
    return 1;
  }
  std::cout << stat << std::endl;
  return 0;
}


