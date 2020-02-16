#include "token.hpp"

token_t::token_t() :
  type(TokenType::INVALID),
  data(""),
  line(1),
  column(0)
{
}
