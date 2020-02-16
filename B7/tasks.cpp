#include "tasks.hpp"
#include <functional>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include "Shape.hpp"
#include "figures.hpp"

void task1()
{
  auto functor = std::bind(std::multiplies<>(), M_PI, std::placeholders::_1);
  std::transform(
    std::istream_iterator<double>(std::cin),
    std::istream_iterator<double>(),
    std::ostream_iterator<double>(std::cout, " "), functor);
  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Input failed");
  }
}

void task2()
{
  std::vector<Shape::ShapePtr> shapes((std::istream_iterator<Shape::ShapePtr>(std::cin)),
                                      std::istream_iterator<Shape::ShapePtr>());
  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Input failed");
  }
  std::cout << "Original:" << std::endl;
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ConstShapePtr>(std::cout, "\n"));
  std::cout << "Left-Right:" << std::endl;
  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isMoreLeft, std::placeholders::_1, std::placeholders::_2));
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ConstShapePtr>(std::cout, "\n"));
  std::cout << "Right-Left:" << std::endl;
  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isMoreLeft, std::placeholders::_2, std::placeholders::_1));
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ConstShapePtr>(std::cout, "\n"));
  std::cout << "Top-Bottom:" << std::endl;
  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isUpper, std::placeholders::_1, std::placeholders::_2));
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ConstShapePtr>(std::cout, "\n"));
  std::cout << "Bottom-Top:" << std::endl;
  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isUpper, std::placeholders::_2, std::placeholders::_1));
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape::ConstShapePtr>(std::cout, "\n"));
}
