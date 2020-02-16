#ifndef LABS_LABS_PHONEBOOKPARSER_HPP
#define LABS_LABS_PHONEBOOKPARSER_HPP


#include <iterator>
#include <unordered_map>
#include <functional>
#include <iostream>
#include "PhoneBookInterface.hpp"
#include "Manipulators.hpp"

class PhoneBookParser
{
public:
  using Command = std::function<void(PhoneBookInterface &)>;
  using Handler = std::function<Command(std::istream &)>;

  static Command add(std::istream &);
  static Command store(std::istream &);
  static Command insert(std::istream &);
  static Command deleteBm(std::istream &);
  static Command show(std::istream &);
  static Command move(std::istream &);
  friend std::istream &operator>>(std::istream &input, PhoneBookParser::Command &command);

private:
  static std::string getLexeme(std::istream &in);

  static bool isValidBookmark(const std::string &);
  static bool isValidNumber(const std::string &);
  static std::string getName(std::istream &in);

  static void invalidInstruction();
  static const Command invalidStep;
  static const std::unordered_map<std::string, PhoneBookParser::Handler> commandDictionary;
};

std::istream &operator>>(std::istream &input, PhoneBookParser::Command &command);
#endif
