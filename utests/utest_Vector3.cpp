#include <iostream>
#include <cmath>

#define BOOST_TEST_MODULE Vector3TemplateTest
#include <boost/test/included/unit_test.hpp>

// First test is if this will compile with including Vector3
#include "Vector3.hpp"

BOOST_AUTO_TEST_SUITE(Vector3Template);

BOOST_AUTO_TEST_CASE(Create_and_Convert)
{
  Vec3f f(1.0, 1.5, 2.0);
  Vec3d d(2.5, 2.55, 2.555);
  Vector3<long double> ld(9.99999999999999, 10.0, std::sqrt(2.0));

  // Make sure all types are expected
  BOOST_TEST(typeid(f).name() == "class Vector3<float>");
  BOOST_TEST(typeid(d).name() == "class Vector3<double>");
  BOOST_TEST(typeid(ld).name() == "class Vector3<long double>");

  // Do a bunch of random operations that (at least conceptually) create ambiguous types (mixing real_type parameter)
  // My code sets the making the return real_type equal to that of the LHS real_type
  auto fdotd = f.dot(d);
  auto dplusf = d + f;
  ld += f;
  auto unit = d.unitize();
  auto ldcrossf = ld.cross(f);
  auto asn = d;
  auto fminusd = f - d;
  f -= ld;
  auto dtimes2 = d * 2;
  f *= 3;
  f /= 3;
  auto lddiv2 = ld / 2;

  // After random operations check if types are what they are expected to be, and if types persisted (they should)
  BOOST_TEST(typeid(fdotd).name() == "double");
  BOOST_TEST(typeid(dplusf).name() == "class Vector3<double>");
  BOOST_TEST(typeid(ld).name() == "class Vector3<long double>");
  BOOST_TEST(typeid(unit).name() == "class Vector3<double>");
  BOOST_TEST(typeid(ldcrossf).name() == "class Vector3<long double>");
  BOOST_TEST(typeid(f[2]).name() == "float");
  BOOST_TEST(typeid(asn).name() == "class Vector3<double>");
  BOOST_TEST(typeid(fminusd).name() == "class Vector3<float>");
  BOOST_TEST(typeid(f).name() == "class Vector3<float>");
  BOOST_TEST(typeid(dtimes2).name() == "class Vector3<double>");
  BOOST_TEST(typeid(lddiv2).name() == "class Vector3<long double>");
}

BOOST_AUTO_TEST_CASE(Numerical_Methods_and_Operations_Valid)
{
  Vec3f f(5.0, -2.5, 3.333);
  Vec3d d(std::sqrt(2.0), 3, std::sqrt(5.0));
  Vec3d one(1.0, 1.0, 1.0);
  Vec3d x(1.0, 0.0, 0.0);
  Vec3d z(0.0, 0.0, 1.0);
  Vec3d four5(0.0, std::sqrt(2) / 2, std::sqrt(2) / 2);

  // Check f to see if values even read out right
  BOOST_CHECK_CLOSE_FRACTION(5.0, f[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-2.5, f[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(3.333, f[2], 0.00001);

  // Check d
  BOOST_CHECK_CLOSE_FRACTION(1.41421356, d[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(3.0, d[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(2.23606797, d[2], 0.00001);

  // Check angle between vectors
  const double pi = std::atan(1) * 4;
  BOOST_CHECK_CLOSE_FRACTION(pi / 2, x.angle(z), 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(pi / 4, four5.angle(z), 0.00001);

  // Check unitized vector and assure magnitude is 1
  auto unit = f.unitize();
  BOOST_CHECK_CLOSE_FRACTION(0.76824, unit[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-0.38412, unit[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(0.51211, unit[2], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(1, unit.magnitude(), 0.00001);

  // Check addition
  auto fplusd = f + d;
  BOOST_CHECK_CLOSE_FRACTION(6.41421356, fplusd[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(0.5, fplusd[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(5.56906797, fplusd[2], 0.00001);

  // Check subtraction
  auto dminusf = d - f;
  BOOST_CHECK_CLOSE_FRACTION(-3.58578643, dminusf[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(5.5, dminusf[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.09693202, dminusf[2], 0.00001);

  // Check magnitude of d
  auto dmgnt = d.magnitude();
  BOOST_CHECK_CLOSE_FRACTION(4.0, dmgnt, 0.00001);

  // Of f
  auto fmgnt = f.magnitude();
  BOOST_CHECK_CLOSE_FRACTION(6.50837068, fmgnt, 0.00001);

  // Check dot product
  auto fdotd = f.dot(d);
  BOOST_CHECK_CLOSE_FRACTION(7.02388238, fdotd, 0.00001);

  // Check cross product
  auto dcrossone = d.cross(one);
  BOOST_CHECK_CLOSE_FRACTION(0.76393202, dcrossone[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(0.82185441, dcrossone[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.58578644, dcrossone[2], 0.00001);

  // Check scalar multiplication
  auto ftimes2 = f * 2.;
  BOOST_CHECK_CLOSE_FRACTION(10.0, ftimes2[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-5.0, ftimes2[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(6.666, ftimes2[2], 0.00001);

  // Check component-wise multiplication
  auto ftimesd = f * d;
  BOOST_CHECK_CLOSE_FRACTION(7.07106781, ftimesd[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-7.5, ftimesd[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(7.45281456, ftimesd[2], 0.00001);

  // Check division
  auto fdiv2 = f / 2.;
  BOOST_CHECK_CLOSE_FRACTION(2.5, fdiv2[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.25, fdiv2[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(1.6665, fdiv2[2], 0.00001);

  // Check subtraction again I guess
  auto fminus1 = f - one;
  BOOST_CHECK_CLOSE_FRACTION(4.0, fminus1[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-3.5, fminus1[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(2.333, fminus1[2], 0.00001);

  // Check negation
  auto negf = -f;
  BOOST_CHECK_CLOSE_FRACTION(-5.0, negf[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(2.5, negf[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-3.333, negf[2], 0.00001);

  //! Do these last because they destroy consist value of vectors

  // Check scalar times equals
  f *= 3.;
  BOOST_CHECK_CLOSE_FRACTION(15, f[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-7.5, f[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(9.999, f[2], 0.00001);

  // Check component-wise times equals
  x *= f;
  BOOST_CHECK_CLOSE_FRACTION(15, x[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(0, x[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(0, x[2], 0.00001);

  // Check divide equals
  f /= -4.;
  BOOST_CHECK_CLOSE_FRACTION(-3.75, f[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(1.875, f[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-2.49975, f[2], 0.00001);

  // Check plus equals
  d += Vec3f(2, 2, 2);
  BOOST_CHECK_CLOSE_FRACTION(3.41421356, d[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(5.0, d[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(4.23606797, d[2], 0.00001);

  // Check minus equals
  d -= Vec3f(6, 6, 6);
  BOOST_CHECK_CLOSE_FRACTION(-2.58578644, d[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.0, d[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.76393203, d[2], 0.00001);
}

BOOST_AUTO_TEST_CASE(IO_Stream_Valid)
{
  Vec3f f(5.0, -2.5, 3.333);
  Vector3<long double> d(std::sqrt(2.0), 3, std::sqrt(5.0));
  Vec3d one(1.0, 1.0, 1.0);
  Vec3d x(1.0, 0.0, 0.0);
  Vec3d z(0.0, 0.0, 1.0);
  Vec3d four5(0.0, std::sqrt(2) / 2, std::sqrt(2) / 2);

  // std::cout << "Input three numbers to create the vector: ";

  // Vec3f input;
  // std::cin >> input;

  // std::cout << "1 (" << typeid(input).name() << "): " << input << std::endl
  std::cout << "2 (" << typeid(f).name() << "): " << f << std::endl
            << "3 (" << typeid(d).name() << "): " << d << std::endl
            << "4 (" << typeid(one).name() << "): " << one << std::endl
            << "5 (" << typeid(x).name() << "): " << x << std::endl
            << "6 (" << typeid(z).name() << "): " << z << std::endl
            << "7 (" << typeid(four5).name() << "): " << four5 << std::endl;
}

BOOST_AUTO_TEST_SUITE_END();