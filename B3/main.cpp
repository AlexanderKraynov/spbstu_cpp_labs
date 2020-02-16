#include "tasks.hpp"
#include <stdexcept>
#include <iostream>

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument{"wrong arguments"};
    }
    const int task = std::stoi(argv[1]);
    switch (task)
    {
      case 1:
        task1();
        break;
      case 2:
        task2();
        break;
      default:
        throw std::invalid_argument{"invalid task"};
    }
    return 0;
  } catch (const std::invalid_argument &exc)
  {
    std::cerr << exc.what() << std::endl;
    return 1;
  } catch (const std::exception &exc)
  {
    std::cerr << exc.what() << std::endl;
    return 2;
  }
}
