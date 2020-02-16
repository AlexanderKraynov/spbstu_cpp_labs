#ifndef LABS_LABS_MANIPULATORS_HPP
#define LABS_LABS_MANIPULATORS_HPP

#include <istream>

std::istream &skipIsBlank(std::istream &in);
std::istream &skipLine(std::istream &in);

class ReadDelimiter
{
public:
  explicit ReadDelimiter(char delimiter);
  char getDelimiter();
private:
  char delimiter;
};

std::istream &operator>>(std::istream &in, ReadDelimiter readDelimiter);

#endif
