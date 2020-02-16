#ifndef LABS_LABS_FORMATITERATOR_HPP
#define LABS_LABS_FORMATITERATOR_HPP

#include <iterator>
#include <memory>
#include "token.hpp"

class FormatIterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
  FormatIterator(std::ostream &out, size_t lineWidth);
  FormatIterator(std::ostream &out);
  FormatIterator &operator*();
  FormatIterator &operator++();
  FormatIterator &operator++(int);
  FormatIterator &operator=(const token_t &token);
private:
  class Line
  {
  public:
    Line(std::ostream &out, size_t lineWidth);
    ~Line();
    void addToken(const token_t &token);
  private:
    std::ostream &out;
    std::string data;
    token_t prev;
    size_t lineWidth;
    bool isFirst;
  };

  std::shared_ptr<Line> linePtr;
};

#endif
