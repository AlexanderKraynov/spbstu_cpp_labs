#include "Shape.hpp"
#include "Manipulators.hpp"

Shape::Shape(const point_t &point) :
  centre(point)
{
}

bool Shape::isMoreLeft(const Shape::ConstShapePtr &rhs) const
{
  return centre.x < rhs->centre.x;
}

bool Shape::isUpper(const Shape::ConstShapePtr &rhs) const
{
  return centre.y > rhs->centre.y;
}

