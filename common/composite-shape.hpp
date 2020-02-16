#ifndef A3_COMPOSITE_SHAPE
#define A3_COMPOSITE_SHAPE

#include <memory>
#include "shape.hpp"
#include "matrix.hpp"

namespace kraynov
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &);
    CompositeShape(CompositeShape &&);
    ~CompositeShape() = default;

    const CompositeShape &operator=(const CompositeShape &);

    const CompositeShape &operator=(CompositeShape &&);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    point_t getPos() const override;

    void move(const point_t &) override;

    void move(double, double) override;

    void scale(double) override;

    void rotate(double) override;

    void add(shape_ptr shape);

    void remove(size_t index);

    int getCount() const;

    Shape::array getArray() const;

    void swap(CompositeShape &);

  private:
    size_t count_;
    double angle_;
    array shapes_;
  };
}

#endif
