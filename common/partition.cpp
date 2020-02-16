#include "partition.hpp"

kraynov::Matrix kraynov::part(const CompositeShape& cShape)
{
  return part(cShape.getArray(), cShape.getCount());
}

kraynov::Matrix kraynov::part(const Shape::array& arr, size_t size)
{
  Matrix matrix;

  for (size_t i = 0; i < size; i++)
  {
    size_t rightRow = 0;
    size_t rightColumn = 0;
    for (size_t j = 0; j < matrix.getRows(); j++)
    {
      for (size_t k = 0; k < matrix.getColumns(); k++)
      {
        if (matrix[j][k] == nullptr)
        {
          rightRow = j;
          rightColumn = k;
          break;
        }

        if (intersect(arr[i]->getFrameRect(), matrix[j][k]->getFrameRect()))
        {
          rightRow = j + 1;
          rightColumn = 0;
          break;
        }
        else
        {
          rightRow = j;
          rightColumn = k + 1;
        }
      }

      if (rightRow == j)
      {
        break;
      }
    }

    matrix.add(arr[i], rightRow, rightColumn);
  }

  return matrix;
}

bool kraynov::intersect(const rectangle_t& lhs, const rectangle_t& rhs)
{
  const point_t lhsTopLeft = {lhs.pos.x - lhs.width / 2, lhs.pos.y + lhs.height / 2};
  const point_t lhsBottomRight = {lhs.pos.x + lhs.width / 2, lhs.pos.y - lhs.height / 2};
  const point_t rhsTopLeft = {rhs.pos.x - rhs.width / 2, rhs.pos.y + rhs.height / 2};
  const point_t rhsBottomRight = {rhs.pos.x + rhs.width / 2, rhs.pos.y - rhs.height / 2};
  const bool topLeftFlag = (lhsTopLeft.x < rhsBottomRight.x) && (rhsBottomRight.y < lhsTopLeft.y);
  const bool bottomRightFlag = (rhsTopLeft.x < lhsBottomRight.x) && (lhsBottomRight.y < rhsTopLeft.y);
  return topLeftFlag && bottomRightFlag;
}
