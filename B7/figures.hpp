#ifndef LABS_LABS_FIGURES_HPP
#define LABS_LABS_FIGURES_HPP

#include "Shape.hpp"

class Circle : public Shape
{
public:
  explicit Circle(const point_t &point);
  void draw(std::ostream &out) const override;
};

class Triangle : public Shape
{
public:
  explicit Triangle(const point_t &point);
  void draw(std::ostream &out) const override;
};

class Square : public Shape
{
public:
  explicit Square(const point_t &point);
  void draw(std::ostream &out) const override;
};

template<typename T>
Shape::ShapePtr constructShapePtr(const point_t &point)
{
  return std::make_shared<T>(point);
}

using ShapeFactory = decltype(&constructShapePtr<Circle>);
const std::unordered_map<std::string, ShapeFactory> shapesMap = {
  {"CIRCLE",   constructShapePtr<Circle>},
  {"TRIANGLE", constructShapePtr<Triangle>},
  {"SQUARE",   constructShapePtr<Square>}
};
std::istream &operator>>(std::istream &in, ShapeFactory &shapeFactory);
std::istream &operator>>(std::istream &input, Shape::ShapePtr &shape);
std::ostream &operator<<(std::ostream &output, const Shape::ConstShapePtr &shape);
#endif
