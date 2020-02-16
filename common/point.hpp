#ifndef LABS_LABS_POINT_HPP
#define LABS_LABS_POINT_HPP

#include <istream>

struct point_t
{
  int x;
  int y;
};

std::istream &operator>>(std::istream &in, point_t &point);
std::ostream &operator<<(std::ostream &out, const point_t &point);

#endif
