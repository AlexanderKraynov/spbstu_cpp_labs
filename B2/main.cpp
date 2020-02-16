#include <iostream>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc == 2)
    {
      const int taskId = std::stoi(argv[1]);
      switch (taskId)
      {
        case 1:
          task1();
          break;
        case 2:
          task2();
          break;
        default:
          throw std::invalid_argument{"invalid task id"};
      }
    }
    else
    {
      throw std::invalid_argument{"invalid program arguments"};
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
