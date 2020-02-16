#ifndef LABS_LABS_TASKPARSER_HPP
#define LABS_LABS_TASKPARSER_HPP

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include "priorityQueue.hpp"

class TaskParser
{
public:
  using StringQueue = PriorityQueue<std::string>;
  using Command = std::function<bool(StringQueue &)>;
  using Handler = std::function<Command(std::string &)>;
  static Command parse(std::string &args);
  static const Command invalidCommand;
private:
  static std::string getLexeme(std::string &);
  static Command parseAdd(std::string &);
  static Command parseGet(std::string &input);
  static Command parseAccelerate(std::string &input);
  static const std::unordered_map<std::string, TaskParser::Handler> commandDictionary;
  static const std::unordered_map<std::string, TaskParser::StringQueue::ElementPriority> priorityDictionary;
};

#endif
