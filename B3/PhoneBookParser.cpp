#include "PhoneBookParser.hpp"

const std::unordered_map<std::string, PhoneBookParser::Handler> PhoneBookParser::commandDictionary =
  {
    {"add",    PhoneBookParser::add},
    {"store",  PhoneBookParser::store},
    {"insert", PhoneBookParser::insert},
    {"delete", PhoneBookParser::deleteBm},
    {"show",   PhoneBookParser::show},
    {"move",   PhoneBookParser::move}
  };

void PhoneBookParser::invalidInstruction()
{
  throw std::invalid_argument("<INVALID COMMAND>\n");
};

const PhoneBookParser::Command PhoneBookParser::invalidStep = [](PhoneBookInterface &)
{
  throw std::invalid_argument("<INVALID STEP>\n");
};

std::string PhoneBookParser::getLexeme(std::istream &in)
{
  in >> skipIsBlank;
  if (in.peek() == '\n')
  {
    return "";
  }
  std::string lexeme;

  in >> lexeme;
  for (auto i : lexeme)
  {
    if (i == '\n')
    {
      return "";
    }
  }
  return lexeme;
}

PhoneBookParser::Command PhoneBookParser::add(std::istream &in)
{
  std::string number = getLexeme(in);
  if (number.empty())
  {
    invalidInstruction();
  }
  if (!isValidNumber(number))
  {
    invalidInstruction();
  }
  std::string name = getName(in);
  return [name, number](PhoneBookInterface &it)
  {
    it.add({name, number});
  };
}

PhoneBookParser::Command PhoneBookParser::deleteBm(std::istream &in)
{
  std::string bookmark = getLexeme(in);
  if (bookmark.empty())
  {
    invalidInstruction();
  }
  return [bookmark](PhoneBookInterface &it)
  {
    it.remove(bookmark);
  };
}

PhoneBookParser::Command PhoneBookParser::store(std::istream &in)
{
  std::string bookmark = getLexeme(in);
  if (bookmark.empty())
  {
    invalidInstruction();
  }
  if (!isValidBookmark(bookmark))
  {
    invalidInstruction();
  }
  std::string newBookMark = getLexeme(in);
  if (newBookMark.empty())
  {
    invalidInstruction();
  }
  return [bookmark, newBookMark](PhoneBookInterface &it)
  {
    it.store(bookmark, newBookMark);
  };
}

bool PhoneBookParser::isValidBookmark(const std::string &markName)
{
  for (char i: markName)
  {
    if (!(isalnum(i) || i == '-'))
    {
      return false;
    }
  }
  return true;
}

PhoneBookParser::Command PhoneBookParser::insert(std::istream &in)
{
  std::string predicate = getLexeme(in);
  if (predicate.empty())
  {
    invalidInstruction();
  }

  if (predicate == "before")
  {
    std::string markName = getLexeme(in);
    if (markName.empty() || !isValidBookmark(markName))
    {
      invalidInstruction();
    }
    std::string number = getLexeme(in);
    if (number.empty())
    {
      invalidInstruction();
    }
    if (!isValidNumber(number))
    {
      invalidInstruction();
    }
    std::string name = getName(in);
    return [markName, number, name](PhoneBookInterface &it)
    {
      it.insertBefore(markName, {name, number});
    };
  }
  else
  {
    if (predicate == "after")
    {
      std::string markName = getLexeme(in);
      if (markName.empty() || !isValidBookmark(markName))
      {
        invalidInstruction();
      }
      std::string number = getLexeme(in);
      if (number.empty())
      {
        invalidInstruction();
      }
      if (!isValidNumber(number))
      {
        invalidInstruction();
      }
      std::string name = getName(in);
      return [markName, number, name](PhoneBookInterface &it)
      {
        it.insertAfter(markName, {name, number});
      };
    }
    else
    {
      invalidInstruction();
    }
  }
  return [](PhoneBookInterface &)
  {};
}

bool PhoneBookParser::isValidNumber(const std::string &number)
{
  for (char i : number)
  {
    if (!isdigit(i))
    {
      return false;
    }
  }
  return true;
}

PhoneBookParser::Command PhoneBookParser::show(std::istream &in)
{
  std::string bookmark = getLexeme(in);
  if (bookmark.empty())
  {
    invalidInstruction();
  }
  return [bookmark](PhoneBookInterface &it)
  {
    it.show(bookmark);
  };
}

PhoneBookParser::Command PhoneBookParser::move(std::istream &in)
{
  std::string markName = getLexeme(in);
  if (markName.empty())
  {
    invalidInstruction();
  }
  std::string steps = getLexeme(in);
  if (steps.empty())
  {
    invalidInstruction();
  }
  if (steps == "first")
  {
    return [markName](PhoneBookInterface &it)
    {
      it.moveToFirst(markName);
    };
  }
  else
  {
    if (steps == "last")
    {
      return [markName](PhoneBookInterface &it)
      {
        it.moveToLast(markName);
      };
    }
    else
    {
      long long int amount = 0;
      try
      {
        amount = std::stoll(steps);
      }
      catch (std::invalid_argument &)
      {
        return invalidStep;
      }
      return [markName, amount](PhoneBookInterface &it)
      {
        it.advance(markName, amount);
      };
    }
  }
}

std::string PhoneBookParser::getName(std::istream &in)
{
  in >> skipIsBlank;
  std::string result;
  size_t trimIndex = 0;
  size_t i = 0;
  while (in.peek() != '\n')
  {
    char curr = in.get();
    if (curr == '\"')
    {
      trimIndex = i;
    }
    result += curr;
    i++;
  }
  result.resize(trimIndex + 1);

  if (result.size() < 2 || result[0] != '"' || result[result.size() - 1] != '"')
  {
    invalidInstruction();
  }
  std::string parsedName;
  for (size_t j = 1; j < result.size() - 1; j++)
  {
    if (result[j] == '\\')
    {
      if ((j + 1 >= result.size()))
      {
        invalidInstruction();
      }
      else
      {
        if ((result[j + 1] == '\\' || result[j + 1] == '"'))
        {
          j++;
          parsedName += result[j];

        }
        else
        {
          invalidInstruction();
        }
      }

    }
    else
    {
      if (result[j] == '\\' || result[j] == '"')
      {
        invalidInstruction();
      }
      else
      {
        parsedName += result[j];
      }
    }
  }
  result = parsedName;
  return result;
}

std::istream &operator>>(std::istream &in, PhoneBookParser::Command &command)
{
  try
  {
    std::istream::sentry sentry(in);
    if (sentry)
    {
      if (in.peek() == std::char_traits<char>::eof())
      {
        command = [](PhoneBookInterface &)
        {};
        return in;
      }
      std::string dictionaryCommand;
      in >> skipIsBlank >> dictionaryCommand;
      auto it = PhoneBookParser::commandDictionary.find(dictionaryCommand);
      if (it != PhoneBookParser::commandDictionary.end())
      {
        command = it->second(in);
        if (in.fail() && !in.eof())
        {
          if (in.bad())
          {
            throw std::ios_base::failure("failed reading command\n");
          }
        }
      }
      else
      {
        command = [](PhoneBookInterface &)
        {
          PhoneBookParser::invalidInstruction();
        };
      }
    }
    else
    {
      command = [](PhoneBookInterface &)
      {
        PhoneBookParser::invalidInstruction();
      };
    }
  }
  catch (std::exception &e)
  {

    std::cout << e.what();
    command = [](PhoneBookInterface &)
    {};
    in >> skipLine;
  }
  return in;
}
