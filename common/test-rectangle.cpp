#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"

const double accuracy = 0.00001;

BOOST_AUTO_TEST_SUITE(rect)

  BOOST_AUTO_TEST_CASE(consistancyInMovement)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    const double initHeight = rect.getFrameRect().height;
    const double initWidth = rect.getFrameRect().width;
    const double initArea = rect.getArea();
    rect.move({0, 0});
    BOOST_CHECK_EQUAL(initWidth, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(initHeight, rect.getFrameRect().height);
    BOOST_CHECK_CLOSE(initArea, rect.getArea(), accuracy);
    rect.move(1, 1);
    BOOST_CHECK_EQUAL(initWidth, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(initHeight, rect.getFrameRect().height);
    BOOST_CHECK_CLOSE(initArea, rect.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(consistancyInScaling)
  {
    kraynov::Rectangle rect({1, 2}, 3, 4);
    const double mult = 1.5;
    const double resultArea = rect.getArea() * mult * mult;
    rect.scale(mult);
    BOOST_CHECK_CLOSE(rect.getArea(), resultArea, accuracy);
  }

  BOOST_AUTO_TEST_CASE(consistancyInRotation)
  {
    kraynov::Rectangle rect({ 7, 2 }, 7.1, 2);
    const double areaBefore = rect.getArea();
    const kraynov::rectangle_t frameRectBefore = rect.getFrameRect();

    double angle = -90;
    rect.rotate(angle);
    double areaAfter = rect.getArea();
    kraynov::rectangle_t frameRectAfter = rect.getFrameRect();

    BOOST_CHECK_CLOSE(frameRectAfter.height, frameRectBefore.width, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.width, frameRectBefore.height, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.x, frameRectBefore.pos.x, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.y, frameRectBefore.pos.y, accuracy);
    BOOST_CHECK_CLOSE(areaAfter, areaBefore, accuracy);

    angle = 180;
    rect.rotate(angle);

    BOOST_CHECK_CLOSE(frameRectAfter.height, frameRectBefore.width, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.width, frameRectBefore.height, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.x, frameRectBefore.pos.x, accuracy);
    BOOST_CHECK_CLOSE(frameRectAfter.pos.y, frameRectBefore.pos.y, accuracy);
    BOOST_CHECK_CLOSE(areaAfter, areaBefore, accuracy);

  }

  BOOST_AUTO_TEST_CASE(IncorrectArgumets)
  {
    BOOST_CHECK_THROW(kraynov::Rectangle({0, 0}, -1, 0), std::invalid_argument);
    BOOST_CHECK_THROW(kraynov::Rectangle({0, 0}, 0, -1), std::invalid_argument);

    kraynov::Rectangle rect({0, 0}, 1.5, 1.5);
    const double mult = -1.5;

    BOOST_CHECK_THROW(rect.scale(mult), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
