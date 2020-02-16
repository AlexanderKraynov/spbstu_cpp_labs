#ifndef LABS_LABS_SHAPE_HPP
#define LABS_LABS_SHAPE_HPP

#include <vector>
#include <iosfwd>
#include "point.hpp"

using Shape = std::vector<point_t>;

bool isSquare(const Shape &shape);
bool isRectangle(const Shape &shape);
bool isTriangle(const Shape &shape);

std::ostream &operator<<(std::ostream &, const Shape &);
std::istream &operator>>(std::istream &, Shape &);

#endif
