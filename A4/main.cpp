#include <stdexcept>
#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "partition.hpp"

void moveBothToPos(kraynov::Shape *first, kraynov::Shape *second, const kraynov::point_t &pos)
{
  if ((first == nullptr) || (second == nullptr)) {
    throw std::invalid_argument("null pointer passed as an argument");
  }
  first->move(pos);
  second->move(pos);
}

bool hasGreaterArea(const kraynov::Shape *first, const kraynov::Shape *second)
{
  if ((first == nullptr) || (second == nullptr)) {
    throw std::invalid_argument("null pointer passed as an argument");
  }
  return first->getArea() > second->getArea();
}

void printFrameRect(const kraynov::Shape *ref)
{
  if (ref == nullptr) {
    throw std::invalid_argument("null pointer passed as an argument");
  }
  kraynov::rectangle_t frameRect = ref->getFrameRect();
  std::cout << "Object's frame Width is " << frameRect.width << std::endl;
  std::cout << "Object's frame Height is " << frameRect.height << std::endl;
  std::cout << "Object's frame Center is positioned at " << frameRect.pos.x << " , " << frameRect.pos.y << std::endl;
}

void scaleAndPrintInfo(kraynov::Shape *ref, double mult)
{
  if (ref == nullptr) {
    throw std::invalid_argument("null pointer passed as an argument");
  }
  ref->scale(mult);
  printFrameRect(ref);
  std::cout << "Object's Area is " << ref->getArea() << std::endl;
}

int main()
{
  kraynov::Circle a({1, 1}, 2);
  kraynov::Rectangle b({2, 2}, 1, 1);
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
  std::cout << "Scaling object a" << std::endl;
  scaleAndPrintInfo(&a, 1.5);
  std::cout << "Including a and b into a composite shape c" << std::endl;
  kraynov::CompositeShape c;
  c.add(std::make_shared<kraynov::Circle>(a));
  c.add(std::make_shared<kraynov::Rectangle>(b));
  std::cout << "There are " << c.getCount() << " objects in composite shape c" << std::endl;
  std::cout << "removing object a" << std::endl;
  c.remove(0);
  std::cout << "There are " << c.getCount() << " objects in composite shape c" << std::endl;
  c.add(std::make_shared<kraynov::Circle>(a));
  kraynov::Rectangle d({6, 6}, 1, 1);
  c.add(std::make_shared<kraynov::Rectangle>(d));

  kraynov::Matrix testMatrix = kraynov::part(c);
  for (size_t i = 0; i < testMatrix.getColumns(); i++) {
    for (size_t j = 0; j < testMatrix.getRows(); j++) {
      if (testMatrix[i][j] != nullptr) {
        std::cout << "shape exists on pos (" << i << "," << j << ")" << std::endl;
      }
    }
  }
  return 0;
}
