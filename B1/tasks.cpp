#include "tasks.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <forward_list>
#include <fstream>
#include <memory>
#include <random>
#include <chrono>
#include "sort.hpp"
#include "printContainer.hpp"

void task1(const std::string &inputCompare)
{
  auto comparator = getComparator<int>(inputCompare);
  std::vector<int> bracketVector;
  int i = 0;

  while (std::cin >> i, !std::cin.eof())
  {
    if (std::cin.fail())
    {
      throw std::runtime_error{"task1 input error"};
    }
    bracketVector.push_back(i);
  }

  if (bracketVector.empty())
  {
    return;
  }

  std::vector<int> atVector(bracketVector);
  std::forward_list<int> itList{bracketVector.begin(), bracketVector.end()};

  sort<BracketAccess>(bracketVector, comparator);
  sort<AtAccess>(atVector, comparator);
  sort<IteratorAccess>(itList, comparator);

  printContainer(bracketVector);
  printContainer(atVector);
  printContainer(itList);
}

void task2(const std::string &filePath)
{
  std::ifstream file(filePath);
  if (!file.is_open())
  {
    throw std::runtime_error{filePath + ": cant open file."};
  }
  typedef std::unique_ptr<char[], decltype(&free)> cArrayPtr;
  size_t currentPos = 0;
  size_t length = 10;
  cArrayPtr cArray{static_cast<char *>(realloc(nullptr, length)), free};
  if (!cArray)
  {
    throw std::runtime_error("task2: error allocating memory.");
  }

  while (!file.eof())
  {
    file.read(&(cArray[currentPos]), length - currentPos);
    currentPos += file.gcount();
    if (currentPos == length)
    {
      length *= 2;
      cArrayPtr cArrayBuf(static_cast< char * >(realloc(cArray.get(), length)), free);
      if (!cArrayBuf)
      {
        throw std::runtime_error("task2: error allocating memory.");
      }
      cArray.swap(cArrayBuf);
      cArrayBuf.release();
    }
    if (!file.eof() && file.fail())
    {
      throw std::runtime_error{filePath + " failed reading from file"};
    }
  }

  if (!currentPos)
  {
    return;
  }
  std::vector<char> data{&cArray[0], &cArray[currentPos]};
  printContainer(data, "", "");
}

void task3()
{
  std::vector<int> data;
  int currentPosition = 0;
  while (std::cin >> currentPosition, !std::cin.eof())
  {
    if (std::cin.fail())
    {
      throw std::runtime_error{"task3 failed to read standard input"};
    }
    if (currentPosition == 0)
    {
      break;
    }
    data.push_back(currentPosition);
  }
  if (data.empty())
  {
    return;
  }

  if (currentPosition != 0)
  {
    throw std::runtime_error("task 3 Input failed: Expected 0 at the end of the input");
  }

  auto curr = data.begin();
  switch (data.back())
  {
    case 1:
    {
      while (curr != data.end())
      {
        if (*curr % 2 == 0)
        {
          curr = data.erase(curr);
        }
        else
        {
          curr++;
        }
      }
      break;
    }
    case 2:
    {
      while (curr != data.end())
      {
        if (*curr % 3 == 0)
        {
          curr = data.insert(curr + 1, 3, 1) + 3;
        }
        else
        {
          curr++;
        }
      }
      break;
    }
  }
  printContainer(data);
}

void fillRandom(double *data, size_t size)
{
  std::uniform_real_distribution<double> distr{-1, 1};
  std::random_device rd;
  std::default_random_engine generator{rd()};
  for (size_t i = 0; i < size; i++)
  {
    data[i] = distr(generator);
  }
}

void task4(const std::string &inputCompare, const std::string &stringSize)
{
  size_t size = std::stoi(stringSize);
  if (size <= 0)
  {
    throw std::invalid_argument("task4: incorrect vector size");
  }
  std::vector<double> sample(size);
  fillRandom(sample.data(), size);
  auto comparator = getComparator<double>(inputCompare);
  printContainer(sample, " ");
  sort<IteratorAccess>(sample, comparator);
  printContainer(sample, " ", "");
}
