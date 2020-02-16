#include "rectangle.hpp"
#include <cassert>

Rectangle::Rectangle(const point_t &pos, double width, double height) :
  pos_(pos),
  width_(width),
  height_(height)
{
  assert((width > 0) && (height > 0) && ("width or height is less or equal to zero"));
}

point_t Rectangle::getPos() const
{
  return pos_;
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, width_, height_};
}

void Rectangle::move(const point_t &pos)
{
  pos_ = pos;
}

void Rectangle::move(double shift_x, double shift_y)
{
  pos_.x += shift_x;
  pos_.y += shift_y;
}
