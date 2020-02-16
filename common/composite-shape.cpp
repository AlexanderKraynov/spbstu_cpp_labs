#include "composite-shape.hpp"
#include <cmath>
#include <stdexcept>

const double FullCircle = 360.0;

kraynov::CompositeShape::CompositeShape() :
  count_(0),
  angle_(0)
{}

kraynov::CompositeShape::CompositeShape(const CompositeShape &comp_shape) :
  count_(comp_shape.count_),
  angle_(comp_shape.angle_),
  shapes_(std::make_unique<shape_ptr[]>(comp_shape.count_))
{
  for (size_t i = 0; i < count_; i++) {
    shapes_[i] = comp_shape.shapes_[i];
  }
}

kraynov::CompositeShape::CompositeShape(CompositeShape &&comp_shape) :
  count_(comp_shape.count_),
  angle_(comp_shape.angle_),
  shapes_(std::move(comp_shape.shapes_))
{}

const kraynov::CompositeShape &kraynov::CompositeShape::operator=(const CompositeShape &comp_shape)
{
  CompositeShape buf(comp_shape);
  swap(buf);
  return *this;
}

const kraynov::CompositeShape &kraynov::CompositeShape::operator=(CompositeShape &&comp_shape)
{
  swap(comp_shape);
  return *this;
}

double kraynov::CompositeShape::getArea() const
{
  double sum = 0;
  for (size_t i = 0; i < count_; i++) {
    sum += shapes_[i]->getArea();
  }
  return sum;
}

kraynov::rectangle_t kraynov::CompositeShape::getFrameRect() const
{
  if (count_ > 0) {
    rectangle_t buf_rect = shapes_[0]->getFrameRect();
    double left = buf_rect.pos.x - buf_rect.width / 2;
    double right = buf_rect.pos.x + buf_rect.width / 2;
    double top = buf_rect.pos.y + buf_rect.height / 2;
    double bottom = buf_rect.pos.y - buf_rect.height / 2;
    for (size_t i = 1; i < count_; i++) {
      buf_rect = shapes_[i]->getFrameRect();
      double buf_left = buf_rect.pos.x - buf_rect.width / 2;
      double buf_right = buf_rect.pos.x + buf_rect.width / 2;
      double buf_top = buf_rect.pos.y + buf_rect.height / 2;
      double buf_bottom = buf_rect.pos.y - buf_rect.height / 2;

      left = std::min(buf_left, left);
      right = std::max(buf_right, right);
      top = std::max(buf_top, top);
      bottom = std::min(buf_bottom, bottom);
    }
    return {{(left + right) / 2, (top + bottom) / 2}, fabs(top - bottom), fabs(right - left)};
  } else {
    return {{0, 0}, 0, 0};
  }
}

kraynov::point_t kraynov::CompositeShape::getPos() const
{
  return getFrameRect().pos;
}

void kraynov::CompositeShape::move(const point_t &pos)
{
  const double shift_x = pos.x - getFrameRect().pos.x;
  const double shift_y = pos.y - getFrameRect().pos.y;
  for (size_t i = 0; i < count_; i++) {
    shapes_[i]->move(shift_x, shift_y);
  }
}

void kraynov::CompositeShape::move(double shift_x, double shift_y)
{
  for (size_t i = 0; i < count_; i++) {
    shapes_[i]->move(shift_x, shift_y);
  }
}

void kraynov::CompositeShape::scale(double multiplicator)
{
  if (multiplicator <= 0) {
    throw std::invalid_argument("Attempted scaling by number lower than 0");
  }
  const point_t centre = getFrameRect().pos;
  for (size_t i = 0; i < count_; i++) {
    shapes_[i]->scale(multiplicator);
    const double shift_x = shapes_[i]->getFrameRect().pos.x - centre.x;
    const double shift_y = shapes_[i]->getFrameRect().pos.y - centre.y;
    shapes_[i]->move({centre.x + shift_x * multiplicator, centre.y + shift_y * multiplicator});
  }
}

void kraynov::CompositeShape::rotate(double angle)
{
  angle_ += angle;
  angle_ = (angle_ < 0.0) ? (FullCircle + fmod(angle_, FullCircle)) : fmod(angle_, FullCircle);

  const point_t centre = getFrameRect().pos;

  for (size_t i = 0; i < count_; i++)
  {
    const double oldX = shapes_[i]->getFrameRect().pos.x - centre.x;
    const double oldY = shapes_[i]->getFrameRect().pos.y - centre.y;

    const double newX = oldX * fabs(cos(angle * M_PI / 180)) - oldY * fabs(sin(angle * M_PI / 180));
    const double newY = oldX * fabs(sin(angle * M_PI / 180)) + oldY * fabs(cos(angle * M_PI / 180));

    shapes_[i]->move({centre.x + newX, centre.y + newY});
    shapes_[i]->rotate(angle);
  }
}


void kraynov::CompositeShape::add(shape_ptr shape)
{
  if (shape == nullptr) {
    throw std::invalid_argument("null pointer passed as a reference");
  }

  array tmpArray(std::make_unique<shape_ptr[]>(count_ + 1));
  for (size_t i = 0; i < count_; i++) {
    tmpArray[i] = shapes_[i];
  }
  tmpArray[count_] = shape;
  count_++;
  shapes_.swap(tmpArray);

}

void kraynov::CompositeShape::remove(size_t index)
{
  if ((index >= count_)) {
    throw std::out_of_range("Index out of range");
  }

  for (size_t i = index; i < count_ - 1; i++) {
    shapes_[i] = shapes_[i + 1];
  }
  count_--;
}

int kraynov::CompositeShape::getCount() const
{
  return count_;
}

kraynov::Shape::array kraynov::CompositeShape::getArray() const
{
  Shape::array tmpArray(std::make_unique<Shape::shape_ptr[]>(count_));
  for (size_t i = 0; i < count_; i++) {
    tmpArray[i] = std::shared_ptr<Shape>(shapes_[i]);
  }

  return tmpArray;
}


void kraynov::CompositeShape::swap(CompositeShape &r)
{
  std::swap(count_, r.count_);
  std::swap(shapes_, r.shapes_);
}
