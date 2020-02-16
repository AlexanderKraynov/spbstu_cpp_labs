#include <exception>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "TokenIterator.hpp"
#include "TokenValidator.hpp"
#include "FormatIterator.hpp"

int main(int argc, char *argv[])
{
  try
  {
    switch (argc)
    {
      case 1:
        std::transform(TokenIterator(std::cin), TokenIterator(), FormatIterator(std::cout), TokenValidator());
        break;
      case 3:
        if (strcmp("--line-width", argv[1]) == 0)
        {
          size_t width = std::stoi(argv[2]);
          std::transform(TokenIterator(std::cin), TokenIterator(), FormatIterator(std::cout, width), TokenValidator());
        }
        else
        {
          throw std::invalid_argument("--line-width expected");
        }
        break;
      default:
        throw std::invalid_argument("Expected 0 arguments or --line-width with 1 argument");
    }

  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
