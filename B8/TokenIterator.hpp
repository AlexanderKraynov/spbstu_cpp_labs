#ifndef LABS_LABS_TOKENITERATOR_HPP
#define LABS_LABS_TOKENITERATOR_HPP

#include <string>
#include <memory>
#include "token.hpp"

class TokenIterator : public std::iterator<std::input_iterator_tag, token_t>
{
public:
  TokenIterator();
  TokenIterator(std::istream &in);
  const token_t &operator*() const;
  bool operator==(const TokenIterator &other);
  bool operator!=(const TokenIterator &other);
  TokenIterator &operator++();
  TokenIterator operator++(int);

private:
  std::istream *in;
  token_t currentToken;
  size_t line;
  size_t column;
  char decimalDelimiter;
};

#endif
