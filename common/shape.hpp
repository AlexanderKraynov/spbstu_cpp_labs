#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP

#include <memory>
#include "base-types.hpp"

namespace kraynov
{
  class Shape
  {
  public:
    using shape_ptr = std::shared_ptr<Shape>;
    using array = std::unique_ptr<shape_ptr[]>;

    virtual ~Shape() = default;

    virtual point_t getPos() const = 0;

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t &dest) = 0;

    virtual void move(double shift_x, double shift_y) = 0;

    virtual void scale(double) = 0;

    virtual void rotate(double) = 0;
  };
}
#endif
