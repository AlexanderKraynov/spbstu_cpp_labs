#include <iostream>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid number of arguments.\n");
    }
    int task = std::stoi(argv[1]);
    switch (task)
    {
      case 1:
      {
        task1();
        break;
      }
      case 2:
      {
        task2();
        break;
      }
      default:
        throw std::invalid_argument("Invalid task id\n");
    }
  } catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  } catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }

}
