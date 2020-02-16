#include <iostream>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc > 1)
    {
      const int task = std::stoi(argv[1]);
      switch (task)
      {
        case 1:
          if (argc == 3)
          {
            task1(argv[2]);
            break;
          }
          throw std::invalid_argument{"wrong arguments for task 1"};

        case 2:
          if (argc == 3)
          {
            task2(argv[2]);
            break;
          }
          throw std::invalid_argument{"wrong arguments for task 2"};
        case 3:
          if (argc == 2)
          {
            task3();
            break;
          }
          throw std::invalid_argument{"wrong arguments for task 3"};
        case 4:
          if (argc == 4)
          {
            task4(argv[2], argv[3]);
            break;
          }
          throw std::invalid_argument{"wrong arguments for task 4"};
        default:
          throw std::invalid_argument{"invalid task number"};
      }
    }
    else
    {
      throw std::invalid_argument{"wrong input parameters: program supports 1 parameter"};
    }
    return 0;
  } catch (const std::invalid_argument &e)
  {
    std::cerr << "invalid argument: " << e.what() << std::endl;
    return 1;
  } catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 2;
  }
}
