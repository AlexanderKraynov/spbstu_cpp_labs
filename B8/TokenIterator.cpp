#include "TokenIterator.hpp"
#include <istream>

TokenIterator::TokenIterator() :
  in(nullptr)
{
}

TokenIterator::TokenIterator(std::istream &in) :
  in(&in),
  line(1),
  column(0)
{
  auto &facet = std::use_facet<std::numpunct<char>>(in.getloc());
  decimalDelimiter = facet.decimal_point();
  operator++();
}

const token_t &TokenIterator::operator*() const
{
  return currentToken;
}

bool TokenIterator::operator==(const TokenIterator &other)
{
  return in == other.in;
}

bool TokenIterator::operator!=(const TokenIterator &other)
{
  return in != other.in;
}

TokenIterator &TokenIterator::operator++()
{
  if (in->eof())
  {
    in = nullptr;
    return *this;
  }
  currentToken.type = token_t::INVALID;
  currentToken.data.clear();
  currentToken.line = line;
  currentToken.column = column;

  char symbol = 0;

  symbol = in->get();


  while (!in->eof())
  {
    column++;
    if (currentToken.type == token_t::DASH && symbol != '-')
    {
      in->putback(symbol);
      in->putback(currentToken.data.back());
      currentToken.data.pop_back();
      currentToken.type = token_t::PUNCTUATION;
      return *this;
    }
    else if (!currentToken.data.empty() && currentToken.data.back() == decimalDelimiter && !isdigit(symbol) &&
             currentToken.type == token_t::NUMBER)
    {
      in->putback(symbol);
      in->putback(currentToken.data.back());
      currentToken.data.pop_back();
      return *this;
    }
    else if (std::isalpha(symbol))
    {
      switch (currentToken.type)
      {
        case token_t::INVALID:
        {
          currentToken.type = token_t::WORD;
          currentToken.data += symbol;
          break;
        }
        case token_t::WORD:
        {
          currentToken.data += symbol;
          break;
        }
        case token_t::DASH:
        case token_t::PUNCTUATION:
        {
          in->putback(symbol);
          return *this;
        }
        case token_t::NUMBER:
        {
          currentToken.type = token_t::INVALID;
          return *this;
        }
      }
    }
    else if (std::isdigit(symbol))
    {
      switch (currentToken.type)
      {
        case token_t::INVALID:
        {
          currentToken.type = token_t::NUMBER;
          currentToken.data += symbol;
          break;
        }
        case token_t::NUMBER:
        {
          currentToken.data += symbol;
          break;
        }
        case token_t::DASH:
        {
          in->putback(symbol);
          return *this;
        }
        case token_t::PUNCTUATION:
        {
          if ((currentToken.data.back() == '+') || (currentToken.data.back() == '-'))
          {
            currentToken.type = token_t::NUMBER;
            currentToken.data += symbol;
            break;
          }
          in->putback(symbol);
          return *this;
        }
        case token_t::WORD:
        {
          currentToken.type = token_t::INVALID;
          return *this;
        }
      }
    }
    else if (isspace(symbol))
    {
      if (symbol == '\n')
      {
        column = 0;
        ++line;
      }
      else if (symbol == '\r')
      {
        column = 0;
      }
      if (!currentToken.data.empty())
      {
        in->putback(symbol);
        return *this;
      }
    }
    else if ((currentToken.type == token_t::NUMBER) && (symbol == decimalDelimiter))
    {
      if (currentToken.data.find(decimalDelimiter) != std::string::npos)
      {
        if (ispunct(symbol))
        {
          in->putback(symbol);
        }
        else
        {
          currentToken.type = token_t::INVALID;
        }
        return *this;
      }
      currentToken.data += symbol;
    }
    else if (symbol == '-')
    {
      switch (currentToken.type)
      {
        case token_t::INVALID:
        {
          currentToken.type = token_t::PUNCTUATION;
          currentToken.data += symbol;
          break;
        }
        case token_t::PUNCTUATION:
        {
          if (currentToken.data.back() == '-')
          {
            currentToken.type = token_t::DASH;
            currentToken.data += symbol;
            break;
          }
          else
          {
            in->putback(symbol);
            return *this;
          }
        }
        case token_t::WORD:
        {
          if (currentToken.data.back() == '-')
          {
            currentToken.data.pop_back();
            in->putback('-');
            in->putback('-');
            return *this;
          }
          else
          {
            currentToken.data += symbol;
            break;
          }
        }
        case token_t::NUMBER:
        {
          in->putback(symbol);
          return *this;
        }
        case token_t::DASH:
        {
          if (currentToken.data.size() > 2)
          {
            currentToken.type = token_t::INVALID;
          }
          else
          {
            currentToken.data.push_back(symbol);
          }
          return *this;
        }
      }
    }
    else if (ispunct(symbol))
    {
      switch (currentToken.type)
      {
        case token_t::INVALID:
        {
          currentToken.type = token_t::PUNCTUATION;
          currentToken.data = symbol;
          break;
        }
        case token_t::DASH:
        case token_t::WORD:
        case token_t::NUMBER:
        case token_t::PUNCTUATION:
        {
          in->putback(symbol);
          return *this;
        }
      }
    }
    else
    {
      return *this;
    }
    symbol = in->get();
  }
  if (currentToken.data.empty())
  {
    in = nullptr;
    return *this;
  }
  return *this;
}

TokenIterator TokenIterator::operator++(int)
{
  TokenIterator tmp = *this;
  operator++();
  return tmp;
}
