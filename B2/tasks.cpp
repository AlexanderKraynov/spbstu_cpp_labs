#include "tasks.hpp"
#include <string>
#include "priorityQueue.hpp"
#include "taskParser.hpp"

void task1()
{
  PriorityQueue<std::string> priorityQueue;
  std::string input;
  while (!std::cin.eof())
  {
    std::getline(std::cin, input);
    TaskParser::parse(input)(priorityQueue);
  }
}

void task2()
{
  std::list<int> data;
  int curr;
  while (std::cin >> curr, !std::cin.eof())
  {
    if (std::cin.fail())
    {
      throw std::runtime_error{"task 2: integer sequence error"};
    }
    if (curr < 1 || curr > 20)
    {
      throw std::out_of_range("task2: element in  [1,20]");
    }
    data.push_back(curr);
  }
  if (data.size() > 20)
  {
    throw std::out_of_range("task2: more than 20 elements detected");
  }
  auto i = data.begin();
  auto j = data.end();
  while (i != j)
  {
    std::cout << *i;
    i++;
    if (j == i)
    {
      break;
    }
    j--;
    std::cout << " " << *(j);
    if (i != j)
    {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}
