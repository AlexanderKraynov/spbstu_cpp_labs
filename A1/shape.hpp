#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  
  virtual point_t getPos() const = 0;
  virtual double getArea() const = 0 ;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t &dest ) = 0;
  virtual void move(double shift_x, double shift_y) = 0;
};
#endif
