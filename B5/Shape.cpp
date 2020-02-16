#include <iterator>
#include <boost/io/ios_state.hpp>
#include "Shape.hpp"
#include "Manipulators.hpp"

std::ostream &operator<<(std::ostream &out, const Shape &shape)
{
  out << shape.size() << " ";
  std::copy(shape.begin(), shape.end(), std::ostream_iterator<point_t>(out, " "));
  return out;
}

std::istream &operator>>(std::istream &in, Shape &shape)
{
  boost::io::ios_flags_saver fs(in);
  in >> std::noskipws;
  size_t size;
  in >> std::ws >> size;
  if (in)
  {
    Shape tmp;
    for (size_t i = 0; i < size; i++)
    {
      point_t buf;
      in >> buf;
      if (!in)
      {
        return in;
      }
      tmp.push_back(buf);
    }
    shape = std::move(tmp);
  }
  return in;
}

bool isRectangle(const Shape &shape)
{
  if (shape.size() != 4)
  {
    return false;
  }
  return (((shape[2].x - shape[1].x) * (shape[0].x - shape[1].x) +
           (shape[2].y - shape[1].y) * (shape[0].y - shape[1].y)) == 0) &
         (((shape[2].x - shape[3].x) * (shape[0].x - shape[3].x) +
           (shape[2].y - shape[3].y) * (shape[0].y - shape[3].y) == 0));
}

bool isSquare(const Shape &shape)
{
  if (!isRectangle(shape))
  {
    return false;
  }
  return ((shape[0].x - shape[2].x) * (shape[1].x - shape[3].x) +
          (shape[0].y - shape[2].y) * (shape[1].y - shape[3].y)) == 0;
}

bool isTriangle(const Shape &shape)
{
  return (shape.size() == 3);
}
