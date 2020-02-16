#ifndef LABS_LABS_TOKEN_HPP
#define LABS_LABS_TOKEN_HPP

#include <cstdio>
#include <string>

struct token_t
{
  enum TokenType
  {
    WORD,
    DASH,
    PUNCTUATION,
    NUMBER,
    INVALID
  };
  token_t();
  TokenType type;
  std::string data;
  size_t line;
  size_t column;
};

#endif
