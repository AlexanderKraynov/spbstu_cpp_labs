#include <unordered_set>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <algorithm>
#include "Shape.hpp"
#include "tasks.hpp"

const auto shapesComparator = [](const Shape &lhs, const Shape &rhs)
{
  if ((lhs.size() == 4) && (rhs.size() == 4))
  {
    if (isSquare(lhs))
    {
      return true;
    }
    if (isSquare(rhs))
    {
      return false;
    }
    return !isRectangle(rhs);
  }
  return lhs.size() < rhs.size();
};


void task1()
{
  std::unordered_set<std::string> words{std::istream_iterator<std::string>{std::cin},
                                        std::istream_iterator<std::string>{}};
  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Input failed.\n");
  }
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>{std::cout, "\n"});
}

void task2()
{
  std::list<Shape> shapes((std::istream_iterator<Shape>(std::cin)), std::istream_iterator<Shape>());
  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Input failed.\n");
  }
  int verticesCounter = std::accumulate(shapes.begin(), shapes.end(), 0, [](int sum, const Shape &it)
  {
    return sum += it.size();
  });
  int squaresCounter = std::count_if(shapes.begin(), shapes.end(), [](const Shape &it)
  {
    return isSquare(it);
  });
  int rectangleCounter = std::count_if(shapes.begin(), shapes.end(), [](const Shape &it)
  {
    return isRectangle(it);
  });
  int triangleCounter = std::count_if(shapes.begin(), shapes.end(), [](const Shape &it)
  {
    return isTriangle(it);
  });
  std::cout << "Vertices: " << verticesCounter << std::endl
            << "Triangles: " << triangleCounter << std::endl
            << "Squares: " << squaresCounter << std::endl
            << "Rectangles: " << rectangleCounter << "\n";
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](const Shape &it)
  {
    return it.size() == 5;
  }), shapes.end());

  Shape points;
  std::for_each(shapes.begin(), shapes.end(), [&points](const Shape &it)
  {
    points.push_back(it[0]);
  });
  std::cout << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<point_t>(std::cout, " "));
  std::cout << std::endl;
  shapes.sort(shapesComparator);
  std::cout << "Shapes:" << std::endl;
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(std::cout, "\n"));
}
