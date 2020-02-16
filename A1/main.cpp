#include <cassert>
#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void moveBothToPos(Shape *first, Shape *second, const point_t &pos)
{
  assert((first != nullptr) && (second != nullptr) && "null pointer passed as an argument");
  first->move(pos);
  second->move(pos);
}

bool hasGreaterArea(const Shape *first, const Shape *second)
{
  assert((first != nullptr) && (second != nullptr) && "null pointer passed as an argument");
  return first->getArea() > second->getArea();
}

void printFrameRect(const Shape *ref)
{
  assert((ref != nullptr) && "null pointer passed as an argument");
  rectangle_t frameRect = ref->getFrameRect();
  std::cout << "Object's frame Width is " << frameRect.width << std::endl;
  std::cout << "Object's frame Height is: " << frameRect.height << std::endl;
  std::cout << "Object's frame Center is positioned at " << frameRect.pos.x << " , " << frameRect.pos.y << std::endl;
}

int main()
{
  Circle a({1, 1}, 2);
  Rectangle b({2, 2}, 1, 1);
  std::cout << "Shape a position is " << a.getPos().x << " , " << a.getPos().y << std::endl;
  std::cout << "Shape b position is " << b.getPos().x << " , " << b.getPos().y << std::endl;
  moveBothToPos(&a, &b, {9, 9});
  
  std::cout << "Shape a position is " << a.getPos().x << " , " << a.getPos().y << std::endl;
  std::cout << "Shape b position is " << b.getPos().x << " , " << b.getPos().y << std::endl;
  if (hasGreaterArea(&a, &b)) {
    std::cout << "a has area greater then b" << std::endl;
  } else {
    std::cout << "a has area not greater then shape b" << std::endl;
  }
  std::cout << "Printing Frame for object a" << std::endl;
  printFrameRect(&a);
  std::cout << "Printing Frame for object b" << std::endl;
  printFrameRect(&b);
  
  return 0;
}
