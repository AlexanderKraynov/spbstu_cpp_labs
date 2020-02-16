#include "matrix.hpp"

#include <stdexcept>
#include <utility>

kraynov::Matrix::Matrix() :
  rows_(0),
  columns_(0)
{}

kraynov::Matrix::Matrix(const Matrix &source) :
  rows_(source.rows_),
  columns_(source.columns_),
  data_(std::make_unique<Shape::shape_ptr[]>(source.rows_ * source.columns_))
{
  for (size_t i = 0; i < (rows_ * columns_); i++) {
    data_[i] = source.data_[i];
  }
}

kraynov::Matrix::Matrix(Matrix &&source) :
  rows_(source.rows_),
  columns_(source.columns_),
  data_(std::move(source.data_))
{
  source.rows_ = 0;
  source.columns_ = 0;
}


const kraynov::Matrix &kraynov::Matrix::operator=(const Matrix &rhs)
{
  if (this != &rhs) {
    Shape::array tmpList(std::make_unique<Shape::shape_ptr[]>(rhs.rows_ * rhs.columns_));
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;

    for (size_t i = 0; i < (rows_ * columns_); i++) {
      tmpList[i] = rhs.data_[i];
    }
    data_.swap(tmpList);
  }

  return *this;
}

const kraynov::Matrix &kraynov::Matrix::operator=(Matrix &&rhs)
{
  if (this != &rhs) {
    std::swap(rows_, rhs.rows_);
    std::swap(columns_, rhs.columns_);
    std::swap(data_, rhs.data_);
  }

  return *this;
}

kraynov::Shape::array kraynov::Matrix::operator[](size_t rhs) const
{
  if (rhs >= rows_) {
    throw std::out_of_range("Index is out of range");
  }

  Shape::array bufData(std::make_unique<Shape::shape_ptr[]>(columns_));
  for (size_t i = 0; i < columns_; i++) {
    bufData[i] = data_[rhs * columns_ + i];
  }

  return bufData;
}

bool kraynov::Matrix::operator==(const Matrix &rhs) const
{
  if ((rows_ != rhs.rows_) || (columns_ != rhs.columns_)) {
    return false;
  }

  for (size_t i = 0; i < (rows_ * columns_); i++) {
    if (data_[i] != rhs.data_[i]) {
      return false;
    }
  }

  return true;
}

bool kraynov::Matrix::operator!=(const Matrix &rhs) const
{
  return !(*this == rhs);
}

void kraynov::Matrix::add(Shape::shape_ptr shape, size_t row, size_t column)
{
  size_t tmpRows = (row == rows_) ? (rows_ + 1) : (rows_);
  size_t tmpColumns = (column == columns_) ? (columns_ + 1) : (columns_);

  Shape::array tmpData(std::make_unique<Shape::shape_ptr[]>(tmpRows * tmpColumns));

  for (size_t i = 0; i < tmpRows; i++) {
    for (size_t j = 0; j < tmpColumns; j++) {
      if ((i == rows_) || (j == columns_)) {
        tmpData[i * tmpColumns + j] = nullptr;
      } else {
        tmpData[i * tmpColumns + j] = data_[i * columns_ + j];
      }
    }
  }
  tmpData[row * tmpColumns + column] = shape;
  data_.swap(tmpData);
  rows_ = tmpRows;
  columns_ = tmpColumns;
}

size_t kraynov::Matrix::getRows() const
{
  return rows_;
}

size_t kraynov::Matrix::getColumns() const
{
  return columns_;
}
