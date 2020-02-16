#include "circle.hpp"
#include <math.h>
#include <cassert>

Circle::Circle(const point_t &pos, double radius) :
  center_(pos),
  radius_(radius)
{
  assert((radius > 0) && "radius is less or equal to zero");
}

point_t Circle::getPos() const
{
  return  center_;
}

double Circle::getArea() const
{
  return  M_PI * pow(radius_,2);
}

void Circle::move(const point_t &dest)
{
  center_ = dest;
}

void Circle::move(double shift_x, double shift_y)
{
  center_.x += shift_x;
  center_.y += shift_y;
}

rectangle_t Circle::getFrameRect() const
{
  return {center_, 2 * radius_, 2 * radius_};
}
