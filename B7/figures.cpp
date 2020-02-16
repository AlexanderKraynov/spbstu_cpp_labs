#include <boost/io/ios_state.hpp>
#include "figures.hpp"

Circle::Circle(const point_t &point) : Shape(point)
{
}

void Circle::draw(std::ostream &out) const
{
  out << "CIRCLE " << centre;
}

Triangle::Triangle(const point_t &point) : Shape(point)
{
}

void Triangle::draw(std::ostream &out) const
{
  out << "TRIANGLE " << centre;
}

Square::Square(const point_t &point) : Shape(point)
{
}

void Square::draw(std::ostream &out) const
{
  out << "SQUARE" << centre;
}

std::istream &operator>>(std::istream &in, ShapeFactory &shapeFactory)
{
  boost::io::ios_flags_saver flags(in);
  in >> std::noskipws;
  in >> std::ws;
  std::string figure;
  while (std::isalpha(in.peek()))
  {
    char letter = 0;
    in >> letter;
    figure += letter;
  }
  if (!in)
  {
    return in;
  }
  auto it = shapesMap.find(figure);
  if (it == shapesMap.end())
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  shapeFactory = it->second;
  return in;
}

std::ostream &operator<<(std::ostream &output, const Shape::ConstShapePtr &shape)
{
  if (shape)
  {
    shape->draw(output);
  }
  return output;
}

std::istream &operator>>(std::istream &in, Shape::ShapePtr &shape)
{
  ShapeFactory shapeFactory;
  point_t centre{};
  in >> shapeFactory >> centre;
  if (!in)
  {
    return in;
  }
  shape = shapeFactory(centre);
  return in;
}
