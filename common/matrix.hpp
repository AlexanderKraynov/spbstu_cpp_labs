#ifndef A4_LABS_MATRIX_HPP
#define A4_LABS_MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace kraynov
{
  class Matrix
  {
  public:
    Matrix();

    Matrix(const Matrix &);
    Matrix(Matrix &&);
    ~Matrix() = default;

    const Matrix &operator=(const Matrix &);
    const Matrix &operator=(Matrix &&);
    Shape::array operator[](std::size_t) const;
    bool operator==(const Matrix &) const;
    bool operator!=(const Matrix &) const;

    void add(Shape::shape_ptr shape, size_t row, size_t column);
    size_t getRows() const;
    size_t getColumns() const;

  private:
    size_t rows_;
    size_t columns_;
    Shape::array data_;
  };
}
#endif
