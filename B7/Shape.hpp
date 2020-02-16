#ifndef LABS_LABS_SHAPE_HPP
#define LABS_LABS_SHAPE_HPP

#include <istream>
#include <memory>
#include <unordered_map>
#include <functional>
#include "point.hpp"

class Shape
{
public:
  using ShapePtr = std::shared_ptr<Shape>;
  using ConstShapePtr = std::shared_ptr<const Shape>;
  explicit Shape(const point_t &point);
  virtual ~Shape() = default;
  bool isMoreLeft(const ConstShapePtr &rhs) const;
  bool isUpper(const ConstShapePtr &rhs) const;
  virtual void draw(std::ostream &) const = 0;
protected:
  point_t centre;
};

#endif
