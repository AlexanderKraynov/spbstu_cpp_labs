#include "taskParser.hpp"
#include <iostream>
#include <algorithm>

const std::unordered_map<std::string, TaskParser::Handler> TaskParser::commandDictionary = {
  {"get",        parseGet},
  {"add",        parseAdd},
  {"accelerate", parseAccelerate},
};
const std::unordered_map<std::string, TaskParser::StringQueue::ElementPriority> TaskParser::priorityDictionary = {
  {"low",    TaskParser::StringQueue::ElementPriority::LOW},
  {"normal", TaskParser::StringQueue::ElementPriority::NORMAL},
  {"high",   TaskParser::StringQueue::ElementPriority::HIGH}
};
const TaskParser::Command TaskParser::invalidCommand = [](StringQueue &)
{
  std::cout << "<INVALID COMMAND>" << std::endl;
  return false;
};

TaskParser::Command TaskParser::parse(std::string &commandS)
{
  if (commandS.empty())
  {
    return [](StringQueue &)
    { return false; };
  }
  std::string command = getLexeme(commandS);
  if (commandDictionary.find(command) == commandDictionary.end())
  {
    return invalidCommand;
  }
  return commandDictionary.at(command)(commandS);
}


std::string TaskParser::getLexeme(std::string &input)
{
  if (input.empty())
  {
    return "";
  }
  input.erase(0, std::distance(input.begin(), find_if(input.begin(), input.end(), [](char i)
  { return !isblank(i); })));
  auto finder = std::find_if(input.begin(), input.end(), isblank);
  if (finder == input.end())
  {
    std::string lexeme = input;
    input = "";
    return lexeme;
  }
  size_t lexemeLength = std::distance(input.begin(), finder);
  size_t trimLength = lexemeLength;
  while (isblank(input[trimLength]))
  {
    trimLength++;
  }
  std::string word = input.substr(0, lexemeLength);
  input.erase(0, trimLength);
  return word;
}

TaskParser::Command TaskParser::parseAdd(std::string &input)
{
  std::string command = getLexeme(input);
  if (priorityDictionary.find(command) == priorityDictionary.end() || input.empty())
  {
    return invalidCommand;
  }
  auto buf = priorityDictionary.at(command);
  return [input, buf](StringQueue &stringQueue)
  { return stringQueue.put(input, buf); };
}

TaskParser::Command TaskParser::parseGet(std::string &)
{
  return [](StringQueue &stringQueue)
  {
    if (!stringQueue.handleFront([](const std::string &str)
                                 { std::cout << str << std::endl; }))
    {
      std::cout << "<EMPTY>" << std::endl;
      return false;
    }
    else
    {
      return true;
    }
  };
}

TaskParser::Command TaskParser::parseAccelerate(std::string &)
{
  return [](StringQueue &stringQueue)
  {
    stringQueue.accelerate();
    return true;
  };
}
