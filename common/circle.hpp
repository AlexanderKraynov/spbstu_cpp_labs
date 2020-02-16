#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

namespace kraynov
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t &pos, double radius);

    point_t getPos() const override;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &dest) override;

    void move(double shift_x, double shift_y) override;

    void scale(double) override;

    void rotate(double) override;

  private:
    point_t center_;
    double radius_;
    double angle_;
  };
}
#endif
