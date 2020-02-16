#include <stdexcept>
#include <boost/test/auto_unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double accuracy = 0.00001;

BOOST_AUTO_TEST_SUITE(testComposite)

  BOOST_AUTO_TEST_CASE(consistancyInMovement)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    kraynov::Circle circ({0, 0}, 2);
    kraynov::CompositeShape cShape;
    cShape.add(std::make_shared<kraynov::Circle>(circ));
    cShape.add(std::make_shared<kraynov::Rectangle>(rect));
    const double initHeight = cShape.getFrameRect().height;
    const double initWidth = cShape.getFrameRect().width;
    const double initArea = cShape.getArea();
    cShape.move({0, 0});
    BOOST_CHECK_EQUAL(initWidth, cShape.getFrameRect().width);
    BOOST_CHECK_EQUAL(initHeight, cShape.getFrameRect().height);
    BOOST_CHECK_CLOSE(initArea, cShape.getArea(), accuracy);
    cShape.move(1, 1);
    BOOST_CHECK_EQUAL(initWidth, cShape.getFrameRect().width);
    BOOST_CHECK_EQUAL(initHeight, cShape.getFrameRect().height);
    BOOST_CHECK_CLOSE(initArea, cShape.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(consistancyInScaling)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    kraynov::Circle circ({0, 0}, 2);
    kraynov::CompositeShape cShape;
    cShape.add(std::make_shared<kraynov::Circle>(circ));
    cShape.add(std::make_shared<kraynov::Rectangle>(rect));

    const double mult = 1.5;
    const double resultArea = cShape.getArea() * mult * mult;
    cShape.scale(mult);
    BOOST_CHECK_CLOSE(cShape.getArea(), resultArea, accuracy);
  }

  BOOST_AUTO_TEST_CASE(consistancyInRotation)
  {
    kraynov::Shape::shape_ptr circ = std::make_shared<kraynov::Circle>(kraynov::point_t { 1, 2 }, 3);
    kraynov::Shape::shape_ptr rect = std::make_shared<kraynov::Rectangle>(kraynov::point_t { 4, 5 }, 9, 2);
    kraynov::CompositeShape testComposition;

    testComposition.add(circ);
    testComposition.add(rect);

    const double areaBefore = testComposition.getArea();
    const kraynov::rectangle_t frameRectBefore = testComposition.getFrameRect();

    double angle = 360;
    testComposition.rotate(angle);

    double areaAfter = testComposition.getArea();
    kraynov::rectangle_t frameRectAfter = testComposition.getFrameRect();

    BOOST_CHECK_CLOSE(frameRectAfter.height, frameRectBefore.height, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.width, frameRectBefore.width, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.x, frameRectBefore.pos.x, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.y, frameRectBefore.pos.y, accuracy);
    BOOST_CHECK_CLOSE(areaAfter, areaBefore, accuracy);

    angle = 90;
    testComposition.rotate(angle);

    areaAfter = testComposition.getArea();
    frameRectAfter = testComposition.getFrameRect();

    BOOST_CHECK_CLOSE(frameRectAfter.height, frameRectBefore.width, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.width, frameRectBefore.height, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.x, frameRectBefore.pos.x, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.y, frameRectBefore.pos.y, accuracy);
    BOOST_CHECK_CLOSE(areaAfter, areaBefore, accuracy);

    angle = -450;
    testComposition.rotate(angle);

    areaAfter = testComposition.getArea();
    frameRectAfter = testComposition.getFrameRect();

    BOOST_CHECK_CLOSE(frameRectAfter.height, frameRectBefore.height, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.width, frameRectBefore.width, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.x, frameRectBefore.pos.x, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.y, frameRectBefore.pos.y, accuracy);
    BOOST_CHECK_CLOSE(areaAfter, areaBefore, accuracy);

  }

  BOOST_AUTO_TEST_CASE(incorrectArgumets)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    kraynov::Circle circ({0, 0}, 2);
    kraynov::CompositeShape cShape;
    cShape.add(std::make_shared<kraynov::Circle>(circ));
    cShape.add(std::make_shared<kraynov::Rectangle>(rect));
    BOOST_CHECK_THROW(cShape.add(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(cShape.remove(4), std::out_of_range);

  }

  BOOST_AUTO_TEST_CASE(copyConstructorConsistancy)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    kraynov::Circle circ({0, 0}, 2);
    kraynov::CompositeShape cShape;
    cShape.add(std::make_shared<kraynov::Circle>(circ));
    cShape.add(std::make_shared<kraynov::Rectangle>(rect));
    const double initArea = cShape.getArea();
    const kraynov::rectangle_t initFrame = cShape.getFrameRect();
    kraynov::CompositeShape cShapeCopy(cShape);
    const kraynov::rectangle_t resFrame = cShapeCopy.getFrameRect();
    BOOST_CHECK_EQUAL(cShape.getCount(), cShapeCopy.getCount());
    BOOST_CHECK_CLOSE(initArea, cShapeCopy.getArea(), accuracy);
    BOOST_CHECK_CLOSE(initFrame.width, resFrame.width, accuracy);
    BOOST_CHECK_CLOSE(initFrame.height, resFrame.height, accuracy);
    BOOST_CHECK_CLOSE(initFrame.pos.x, resFrame.pos.x, accuracy);
    BOOST_CHECK_CLOSE(initFrame.pos.y, resFrame.pos.y, accuracy);
  }

  BOOST_AUTO_TEST_CASE(copyOperatorConsistancy)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    kraynov::Circle circ({0, 0}, 2);
    kraynov::CompositeShape cShape;
    cShape.add(std::make_shared<kraynov::Circle>(circ));
    cShape.add(std::make_shared<kraynov::Rectangle>(rect));
    const double initArea = cShape.getArea();
    const kraynov::rectangle_t initFrame = cShape.getFrameRect();
    kraynov::CompositeShape cShapeCopy;
    cShapeCopy = cShape;
    const kraynov::rectangle_t resFrame = cShapeCopy.getFrameRect();
    BOOST_CHECK_EQUAL(cShape.getCount(), cShapeCopy.getCount());
    BOOST_CHECK_CLOSE(initArea, cShapeCopy.getArea(), accuracy);
    BOOST_CHECK_CLOSE(initFrame.width, resFrame.width, accuracy);
    BOOST_CHECK_CLOSE(initFrame.height, resFrame.height, accuracy);
    BOOST_CHECK_CLOSE(initFrame.pos.x, resFrame.pos.x, accuracy);
    BOOST_CHECK_CLOSE(initFrame.pos.y, resFrame.pos.y, accuracy);
  }

  BOOST_AUTO_TEST_CASE(moveConstructorConsistancy)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    kraynov::Circle circ({0, 0}, 2);
    kraynov::CompositeShape cShape;
    cShape.add(std::make_shared<kraynov::Circle>(circ));
    cShape.add(std::make_shared<kraynov::Rectangle>(rect));
    const double initArea = cShape.getArea();
    const kraynov::rectangle_t initFrame = cShape.getFrameRect();
    const int initCount = cShape.getCount();
    kraynov::CompositeShape cShapeCopy(std::move(cShape));
    const kraynov::rectangle_t resFrame = cShapeCopy.getFrameRect();
    BOOST_CHECK_EQUAL(initCount, cShapeCopy.getCount());
    BOOST_CHECK_CLOSE(initArea, cShapeCopy.getArea(), accuracy);
    BOOST_CHECK_CLOSE(initFrame.width, resFrame.width, accuracy);
    BOOST_CHECK_CLOSE(initFrame.height, resFrame.height, accuracy);
    BOOST_CHECK_CLOSE(initFrame.pos.x, resFrame.pos.x, accuracy);
    BOOST_CHECK_CLOSE(initFrame.pos.y, resFrame.pos.y, accuracy);
  }

  BOOST_AUTO_TEST_CASE(moveOperatorConsistancy)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    kraynov::Circle circ({0, 0}, 2);
    kraynov::CompositeShape cShape;
    cShape.add(std::make_shared<kraynov::Circle>(circ));
    cShape.add(std::make_shared<kraynov::Rectangle>(rect));
    const double initArea = cShape.getArea();
    const kraynov::rectangle_t initFrame = cShape.getFrameRect();
    const int initCount = cShape.getCount();
    kraynov::CompositeShape cShapeCopy;
    cShapeCopy = std::move(cShape);
    const kraynov::rectangle_t resFrame = cShapeCopy.getFrameRect();
    BOOST_CHECK_EQUAL(initCount, cShapeCopy.getCount());
    BOOST_CHECK_CLOSE(initArea, cShapeCopy.getArea(), accuracy);
    BOOST_CHECK_CLOSE(initFrame.width, resFrame.width, accuracy);
    BOOST_CHECK_CLOSE(initFrame.height, resFrame.height, accuracy);
    BOOST_CHECK_CLOSE(initFrame.pos.x, resFrame.pos.x, accuracy);
    BOOST_CHECK_CLOSE(initFrame.pos.y, resFrame.pos.y, accuracy);
  }


BOOST_AUTO_TEST_SUITE_END()
