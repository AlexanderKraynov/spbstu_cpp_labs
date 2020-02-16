#include <stdexcept>
#include <utility>

#include <boost/test/auto_unit_test.hpp>
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "partition.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(testMatrix)

  BOOST_AUTO_TEST_CASE(testCopyConstructor)
  {
    kraynov::Shape::shape_ptr circ = std::make_shared<kraynov::Circle>(kraynov::point_t { 1, 2}, 3);
    kraynov::Shape::shape_ptr rect = std::make_shared<kraynov::Rectangle>(kraynov::point_t { 4, 5 }, 6, 7);
    kraynov::CompositeShape cShape;

    cShape.add(circ);
    cShape.add(rect);

    kraynov::Matrix testMatrix = kraynov::part(cShape);
    kraynov::Matrix testMatrixCopy(testMatrix);

    BOOST_CHECK(testMatrix == testMatrixCopy);
    BOOST_CHECK_EQUAL(testMatrixCopy.getRows(), testMatrix.getRows());
    BOOST_CHECK_EQUAL(testMatrixCopy.getColumns(), testMatrix.getColumns());
  }

  BOOST_AUTO_TEST_CASE(testMoveConstructor)
  {
    kraynov::Shape::shape_ptr circ = std::make_shared<kraynov::Circle>(kraynov::point_t { 1, 2 }, 3);
    kraynov::Shape::shape_ptr rect = std::make_shared<kraynov::Rectangle>(kraynov::point_t { 1, 2 }, 1, 6);
    kraynov::CompositeShape cShape;

    cShape.add(circ);
    cShape.add(rect);

    kraynov::Matrix testMatrix = kraynov::part(cShape);
    kraynov::Matrix testMatrixCopy(testMatrix);
    kraynov::Matrix testMatrixMove = std::move(testMatrix);

    BOOST_CHECK(testMatrixMove == testMatrixCopy);
    BOOST_CHECK_EQUAL(testMatrixMove.getRows(), testMatrixCopy.getRows());
    BOOST_CHECK_EQUAL(testMatrixMove.getColumns(), testMatrixCopy.getColumns());;
  }

  BOOST_AUTO_TEST_CASE(testCopyOperator)
  {
    kraynov::Shape::shape_ptr circ = std::make_shared<kraynov::Circle>(kraynov::point_t { 1, 2}, 3);
    kraynov::Shape::shape_ptr rect = std::make_shared<kraynov::Rectangle>(kraynov::point_t { 4, 5 }, 6, 7);
    kraynov::CompositeShape cShape;

    cShape.add(circ);
    cShape.add(rect);

    kraynov::Matrix testMatrix = kraynov::part(cShape);
    kraynov::Matrix testMatrixCopy;
    testMatrixCopy = testMatrix;

    BOOST_CHECK(testMatrixCopy == testMatrix);
    BOOST_CHECK_EQUAL(testMatrixCopy.getRows(), testMatrix.getRows());
    BOOST_CHECK_EQUAL(testMatrixCopy.getColumns(), testMatrix.getColumns());;
  }

  BOOST_AUTO_TEST_CASE(testMoveOperator)
  {
    kraynov::Shape::shape_ptr circ = std::make_shared<kraynov::Circle>(kraynov::point_t { 1, 2}, 3);
    kraynov::Shape::shape_ptr rect = std::make_shared<kraynov::Rectangle>(kraynov::point_t { 4, 5 }, 6, 7);
    kraynov::CompositeShape cShape;

    cShape.add(circ);
    cShape.add(rect);

    kraynov::Matrix testMatrix = kraynov::part(cShape);
    kraynov::Matrix testMatrixCopy(testMatrix);
    kraynov::Matrix testMatrixMove;
    testMatrixMove = std::move(testMatrix);

    BOOST_CHECK(testMatrixMove == testMatrixCopy);
    BOOST_CHECK_EQUAL(testMatrixMove.getRows(), testMatrixCopy.getRows());
    BOOST_CHECK_EQUAL(testMatrixMove.getColumns(), testMatrixCopy.getColumns());;
  }


  BOOST_AUTO_TEST_CASE(outOfRange)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    kraynov::Circle circ({0, 0}, 2);
    kraynov::CompositeShape testComposite;
    testComposite.add(std::make_shared<kraynov::Circle>(circ));
    testComposite.add(std::make_shared<kraynov::Rectangle>(rect));

    kraynov::Matrix testMatrix = kraynov::part(testComposite);

    BOOST_CHECK_THROW(testMatrix[3], std::out_of_range);
    BOOST_CHECK_THROW(testMatrix[-1], std::out_of_range);
  }
  BOOST_AUTO_TEST_CASE(matrixThrowExceptionAfterUsingOfOperator)
  {
    const kraynov::Rectangle testRectangle1({4, 3},2, 7);
    kraynov::Shape::shape_ptr rect1 = std::make_shared<kraynov::Rectangle>(testRectangle1);
    const kraynov::Rectangle testRectangle2({5, 7},1, 3);
    kraynov::Shape::shape_ptr  rect2 = std::make_shared<kraynov::Rectangle>(testRectangle2);
    const kraynov::Circle testCircle1({-1, 3},4);
    kraynov::Shape::shape_ptr  circ1 = std::make_shared<kraynov::Circle>(testCircle1);
    const kraynov::Circle testCircle2({-3, 5},1);
    kraynov::Shape::shape_ptr  circ2 = std::make_shared<kraynov::Circle>(testCircle2);

    kraynov::CompositeShape cShape;
    cShape.add(rect1);
    cShape.add(circ1);
    cShape.add(rect2);
    cShape.add(circ2);

    kraynov::Matrix matrix = part(cShape);

    BOOST_CHECK_THROW(matrix[10][5], std::out_of_range);
  }
  BOOST_AUTO_TEST_CASE(testAddingToMatrix)
  {
    kraynov::Shape::shape_ptr testCircle = std::make_shared<kraynov::Circle>(kraynov::point_t{0, 0}, 2);
    kraynov::Shape::shape_ptr testRectangle1 = std::make_shared<kraynov::Rectangle>(kraynov::point_t{14, 12}, 2, 1);
    kraynov::Shape::shape_ptr testRectangle2 = std::make_shared<kraynov::Rectangle>(kraynov::point_t{0, 0}, 24, 12);
    kraynov::CompositeShape testComposite;
    testComposite.add(testCircle);
    testComposite.add(testRectangle1);
    testComposite.add(testRectangle2);
    size_t rows = 2;
    size_t columns = 2;
    kraynov::Matrix testMatrix = kraynov::part(testComposite);

    BOOST_CHECK_EQUAL(rows, testMatrix.getRows());
    BOOST_CHECK_EQUAL(columns, testMatrix.getColumns());

    kraynov::Shape::shape_ptr testRectangle3 = std::make_shared<kraynov::Rectangle>(kraynov::point_t{1, 3}, 20, 12);

    testMatrix.add(testRectangle3, rows, columns);
    rows++;

    kraynov::Shape::shape_ptr testCircle2 = std::make_shared<kraynov::Circle>(kraynov::point_t{-100, -40}, 6);

    testMatrix.add(testCircle2, 0, columns);
    columns++;

    BOOST_CHECK_EQUAL(rows, testMatrix.getRows());
    BOOST_CHECK_EQUAL(columns, testMatrix.getColumns());
  }

BOOST_AUTO_TEST_SUITE_END()
