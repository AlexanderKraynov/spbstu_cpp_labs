#ifndef A4_LABS_PARTITION_HPP
#define A4_LABS_PARTITION_HPP

#include "composite-shape.hpp"
#include "matrix.hpp"
#include "base-types.hpp"

namespace kraynov
{
  Matrix part(const Shape::array &, size_t);
  Matrix part(const CompositeShape &);
  bool intersect(const rectangle_t &, const rectangle_t &);
}


#endif
