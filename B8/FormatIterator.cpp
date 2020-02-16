#include "FormatIterator.hpp"

#define DEFAULT_LINE_WIDTH 40

FormatIterator::Line::Line(std::ostream &out, size_t lineWidth) :
  out(out),
  lineWidth(lineWidth),
  isFirst(true)
{
}

FormatIterator::Line::~Line()
{
  out << data << std::endl;
}

void FormatIterator::Line::addToken(const token_t &token)
{
  size_t wrapping = 0;
  if (isFirst)
  {
    data = token.data;
    prev = token;
  }

  if (token.type != token_t::PUNCTUATION && token.type != token_t::DASH)
  {
    wrapping = data.size();
  }
  else if (prev.type != token_t::PUNCTUATION)
  {
    wrapping = data.size() - prev.data.size() - 1;
  }
  if (!isFirst)
  {
    if (token.type == token_t::PUNCTUATION)
    {
      data += token.data;
    }
    else
    {
      data += " " + token.data;
    }
  }
  isFirst = false;
  if (data.size() > lineWidth)
  {
    out.write(data.c_str(), wrapping);
    out << std::endl;
    data.erase(0, wrapping);
    if (isblank(data.front()))
    {
      data.erase(data.begin());
    }
  }
  prev = token;
}


FormatIterator::FormatIterator(std::ostream &out, size_t lineWidth) :
  linePtr(std::make_shared<Line>(out, lineWidth))
{
  if (lineWidth < 25)
  {
    throw std::invalid_argument("Invalid line width ");
  }
}

FormatIterator &FormatIterator::operator*()
{
  return *this;
}

FormatIterator &FormatIterator::operator++()
{
  return *this;
}

FormatIterator &FormatIterator::operator++(int)
{
  return *this;
}

FormatIterator &FormatIterator::operator=(const token_t &token)
{
  linePtr->addToken(token);
  return *this;
}

FormatIterator::FormatIterator(std::ostream &out) :
  FormatIterator(out, DEFAULT_LINE_WIDTH)
{
}
