#ifndef LABS_LABS_TOKENVALIDATOR_HPP
#define LABS_LABS_TOKENVALIDATOR_HPP

#include "token.hpp"

class TokenValidator
{
public:
  token_t operator()(const token_t &token);
private:
  token_t prev;
};

#endif
