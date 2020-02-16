#include <boost/test/auto_unit_test.hpp>
#include <memory>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "partition.hpp"


const double accuracy = 0.00001;

BOOST_AUTO_TEST_SUITE(testPartition)

  BOOST_AUTO_TEST_CASE(intersectionIsRight)
  {
    kraynov::Circle circ1({-1, 2}, 2);
    kraynov::Circle circ2({0, 1}, 4);
    kraynov::Rectangle rect1({1, 2}, 5, 4);
    kraynov::Rectangle rect2({7, 7}, 3, 0.1);


    BOOST_CHECK(intersect(rect1.getFrameRect(), circ1.getFrameRect()));
    BOOST_CHECK(intersect(rect1.getFrameRect(), circ2.getFrameRect()));
    BOOST_CHECK(!intersect(rect1.getFrameRect(), rect2.getFrameRect()));
    BOOST_CHECK(!intersect(circ1.getFrameRect(), rect2.getFrameRect()));
    BOOST_CHECK(!intersect(circ2.getFrameRect(), rect2.getFrameRect()));

  }

  BOOST_AUTO_TEST_CASE(partitionIsRight)
  {
    kraynov::Rectangle rec1({ { 7, 6 }, 4, 2 });
    kraynov::Rectangle rec2({ { 10, 3 }, 4, 2 });
    kraynov::Circle cir1({ 4, 4 }, 2);
    kraynov::Circle cir2({ 10, 8 }, 2);

    kraynov::CompositeShape composite;
    composite.add(std::make_shared<kraynov::Circle>(cir1));
    composite.add(std::make_shared<kraynov::Rectangle>(rec1));
    composite.add(std::make_shared<kraynov::Rectangle>(rec2));
    composite.add(std::make_shared<kraynov::Circle>(cir2));

    kraynov::Matrix matrix = kraynov::part(composite);

    BOOST_CHECK_EQUAL(matrix.getRows(), 2);
    BOOST_CHECK_EQUAL(matrix.getColumns(), 3);
    BOOST_CHECK_EQUAL(matrix[0][0]->getArea(), cir1.getArea());
    BOOST_CHECK_EQUAL(matrix[1][0]->getArea(), rec1.getArea());
  }
  BOOST_AUTO_TEST_CASE(testPartitionExeptions)
  {
    kraynov::Rectangle rec1({ { 0, 0 }, 1, 1 });
    kraynov::Rectangle rec2({ { 0, 0 }, 1, 1 });
    kraynov::Rectangle rec3({ { 0, 0 }, 1, 1 });
    kraynov::Circle cir1({ 50, 50 }, 2);
    kraynov::Circle cir2({ 50, 50 }, 2);

    kraynov::CompositeShape composite;
    composite.add(std::make_shared<kraynov::Rectangle>(rec1));
    composite.add(std::make_shared<kraynov::Rectangle>(rec2));
    composite.add(std::make_shared<kraynov::Rectangle>(rec3));
    composite.add(std::make_shared<kraynov::Circle>(cir1));
    composite.add(std::make_shared<kraynov::Circle>(cir2));

    kraynov::Matrix matrix = kraynov::part(composite);

    BOOST_CHECK_THROW(matrix[4][4],std::out_of_range);
    BOOST_CHECK_THROW(matrix[3][3],std::out_of_range);
  }


BOOST_AUTO_TEST_SUITE_END()
