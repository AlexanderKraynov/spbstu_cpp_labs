#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP


#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &pos, double width, double height);
  
  point_t getPos() const override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &pos) override;
  void move( double shift_x, double shift_y) override;

private:
  point_t pos_;
  double width_;
  double height_;
};

#endif
