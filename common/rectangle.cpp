#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>

const double FullCircle = 360.0;

kraynov::Rectangle::Rectangle(const point_t &pos, double width, double height) :
  pos_(pos),
  width_(width),
  height_(height),
  angle_(0)
{
  if ((width <= 0) || (height <= 0))
  {
    throw std::invalid_argument("Attempted creation of a rectangle with width or height less than 0");
  }
}

kraynov::point_t kraynov::Rectangle::getPos() const
{
  return pos_;
}

double kraynov::Rectangle::getArea() const
{
  return width_ * height_;
}

kraynov::rectangle_t kraynov::Rectangle::getFrameRect() const
{
  const double width = height_ * fabs(sin(angle_ * M_PI / 180)) + width_ * fabs(cos(angle_ * M_PI / 180));
  const double height = height_ * fabs(cos(angle_ * M_PI / 180)) + width_ * fabs(sin(angle_ * M_PI / 180));


  return {pos_, width, height};
}

void kraynov::Rectangle::move(const point_t &pos)
{
  pos_ = pos;
}

void kraynov::Rectangle::move(double shift_x, double shift_y)
{
  pos_.x += shift_x;
  pos_.y += shift_y;
}

void kraynov::Rectangle::scale(double multiplicator)
{
  if (multiplicator <= 0)
  {
    throw std::invalid_argument("Attempted scaling by number lower than 0");
  }
  height_ *= multiplicator;
  width_ *= multiplicator;
}

void kraynov::Rectangle::rotate(double angle)
{
  angle_ += angle;
  angle_ = (angle_ < 0.0) ? (FullCircle + fmod(angle_, FullCircle)) : fmod(angle_, FullCircle);
}

