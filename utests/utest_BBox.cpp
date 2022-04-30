#include <iostream>
#include <cmath>
#include <string>

#define BOOST_TEST_MODULE BoundingBoxTest
#include <boost/test/included/unit_test.hpp>

// First test is if this will compile with including Vector3
#include "BBox.hpp"

BOOST_AUTO_TEST_SUITE(BoundingBox);

BOOST_AUTO_TEST_CASE(Test)
{
    BBox b1;
    Ray r1(Vec3d(), Vec3d(0, 0, -1));
    Ray r2(Vec3d(), Vec3d(0, 0, 1));
    Ray r3(Vec3d(1.25, 1.25, 0.25), Vec3d(-1, -1, -2));
    Ray r4(Vec3d(), Vec3d(-2, -2, -1));

    BBox b2(Vec3d(-10, -300, -8), Vec3d(302, 300, 600));
    Ray r5(Vec3d(80, -100, 300), Vec3d(0.1871, 0.6359, -0.7488));

    double t;
    BOOST_TEST(b1.hit(r1, 1, INFINITY, t));
    BOOST_TEST(!b1.hit(r2, 1, INFINITY, t));
    BOOST_TEST(b1.hit(r3, 1, INFINITY, t));
    BOOST_TEST(!b1.hit(r4, 1, INFINITY, t));
    BOOST_TEST(b2.hit(r5, 1, INFINITY, t));
}

BOOST_AUTO_TEST_SUITE_END();