#include <bits/ios_base.h>
#include "TokenValidator.hpp"

#define MAX_TOKEN_SIZE 20

token_t TokenValidator::operator()(const token_t &token)
{
  if (prev.data.empty())
  {
    if (token.type == token_t::PUNCTUATION || token.type == token_t::DASH)
    {
      throw std::ios_base::failure("Test starts with punctuation.");
    }
  }
  if (prev.type == token_t::PUNCTUATION || prev.type == token_t::DASH)
  {
    if (token.type == token_t::PUNCTUATION)
    {
      throw std::ios_base::failure("Punctuation sign is being followed by punctuation sign.");
    }
    if (token.type == token_t::DASH)
    {
      if (prev.data != ",")
      {
        throw std::ios_base::failure("Punctuation sign is being followed by punctuation sign.");
      }
    }
  }
  if (((token.type == token_t::WORD) || token.type == token_t::NUMBER) && (token.data.size() > MAX_TOKEN_SIZE))
  {
    throw std::ios_base::failure("max token size is " + std::to_string(MAX_TOKEN_SIZE));
  }
  prev = token;
  return token;
}
