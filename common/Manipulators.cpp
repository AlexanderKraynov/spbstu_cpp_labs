#include "Manipulators.hpp"

std::istream &skipIsBlank(std::istream &in)
{
  while (isblank(in.peek()))
  {
    in.get();
  }
  return in;
}

std::istream &skipLine(std::istream &in)
{
  while (in.peek() != '\n' && !in.eof())
  {
    in.get();
  }
  if (in.peek() == '\n')
  {
    in.get();
  }
  return in;
}

ReadDelimiter::ReadDelimiter(char delimiter)
  : delimiter(delimiter)
{
}

char ReadDelimiter::getDelimiter()
{
  return delimiter;
}

std::istream &operator>>(std::istream &in, ReadDelimiter readDelimiter)
{
  if (in.peek() != readDelimiter.getDelimiter())
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.get();
  return in;
}
