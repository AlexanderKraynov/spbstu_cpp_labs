#include <boost/io/ios_state.hpp>
#include "point.hpp"
#include "Manipulators.hpp"

std::istream &operator>>(std::istream &in, point_t &point)
{
  boost::io::ios_flags_saver fs(in);
  in >> std::noskipws >> skipIsBlank >> ReadDelimiter('(') >> skipIsBlank >> point.x >> skipIsBlank
     >> ReadDelimiter(';') >> skipIsBlank
     >> point.y >> skipIsBlank >> ReadDelimiter(')');
  if (!in)
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const point_t &point)
{
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}
