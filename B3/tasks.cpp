#include "tasks.hpp"
#include <cstdio>
#include "PhoneBookParser.hpp"
#include "FactorialContainer.hpp"


void task1()
{
  PhoneBookInterface pBook;
  std::for_each(std::istream_iterator<PhoneBookParser::Command>(std::cin >> std::noskipws),
                std::istream_iterator<PhoneBookParser::Command>(),
                [&](auto &command)
                {
                  try
                  {
                    command(pBook);
                  }
                  catch (std::exception &e)
                  {
                    std::cout << e.what();
                  }

                  std::cin >> std::ws;
                });
}

void task2()
{
  FactorialContainer container(11);
  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << std::endl;
  std::copy(std::make_reverse_iterator(container.end()), std::make_reverse_iterator(container.begin()),
            std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << std::endl;
}
