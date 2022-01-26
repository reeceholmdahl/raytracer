#include <iostream>
#include <cmath>

#define BOOST_TEST_MODULE Vector3TemplateTest
#include <boost/test/included/unit_test.hpp>

// First test is if this will compile with including Vector3
#include "Vector3.h"

BOOST_AUTO_TEST_SUITE(Vector3Template)

BOOST_AUTO_TEST_CASE(Create_and_Convert)
{
  Vec3f f(1.0, 1.5, 2.0);
  Vec3d d(2.5, 2.55, 2.555);
  Vector3<long double> ld(9.99999999999999, 10.0, std::sqrt(2.0));

  BOOST_TEST(typeid(f).name() == "class Vector3<float>");
  BOOST_TEST(typeid(d).name() == "class Vector3<double>");
  BOOST_TEST(typeid(ld).name() == "class Vector3<long double>");

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

BOOST_AUTO_TEST_CASE(Methods_and_Operations_Valid)
{
  Vec3f f(5.0, -2.5, 3.333);
  Vec3d d(std::sqrt(2.0), 3, std::sqrt(5.0));
  Vec3d one(1.0, 1.0, 1.0);

  // Check them to see if they even read out right
  BOOST_CHECK_CLOSE_FRACTION(5.0, f[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-2.5, f[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(3.333, f[2], 0.00001);

  BOOST_CHECK_CLOSE_FRACTION(1.41421356, d[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(3.0, d[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(2.23606797, d[2], 0.00001);

  auto fplusd = f + d;
  BOOST_CHECK_CLOSE_FRACTION(6.41421356, fplusd[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(0.5, fplusd[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(5.56906797, fplusd[2], 0.00001);

  auto dminusf = d - f;
  BOOST_CHECK_CLOSE_FRACTION(-3.58578643, dminusf[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(5.5, dminusf[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.09693202, dminusf[2], 0.00001);

  auto dmgnt = d.magnitude();
  BOOST_CHECK_CLOSE_FRACTION(4.0, dmgnt, 0.00001);

  auto fmgnt = f.magnitude();
  BOOST_CHECK_CLOSE_FRACTION(6.50837068, fmgnt, 0.00001);

  auto fdotd = f.dot(d);
  BOOST_CHECK_CLOSE_FRACTION(7.02388238, fdotd, 0.00001);

  auto dcrossone = d.cross(one);
  BOOST_CHECK_CLOSE_FRACTION(0.76393202, dcrossone[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(0.82185441, dcrossone[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.58578644, dcrossone[2], 0.00001);

  auto ftimes2 = f * 2.;
  BOOST_CHECK_CLOSE_FRACTION(10.0, ftimes2[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-5.0, ftimes2[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(6.666, ftimes2[2], 0.00001);

  auto fdiv2 = f / 2.;
  BOOST_CHECK_CLOSE_FRACTION(2.5, fdiv2[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.25, fdiv2[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(1.6665, fdiv2[2], 0.00001);

  auto fminus1 = f - one;
  BOOST_CHECK_CLOSE_FRACTION(4.0, fminus1[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-3.5, fminus1[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(2.333, fminus1[2], 0.00001);

  auto negf = -f;
  BOOST_CHECK_CLOSE_FRACTION(-5.0, negf[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(2.5, negf[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-3.333, negf[2], 0.00001);

  // Do these last because they destroy consist value of vectors
  f *= 3.;
  BOOST_CHECK_CLOSE_FRACTION(15.0, f[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-7.5, f[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(9.999, f[2], 0.00001);

  f /= -4.;
  BOOST_CHECK_CLOSE_FRACTION(-3.75, f[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(1.875, f[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-2.49975, f[2], 0.00001);

  d += Vec3f(2, 2, 2);
  BOOST_CHECK_CLOSE_FRACTION(3.41421356, d[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(5.0, d[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(4.23606797, d[2], 0.00001);

  d -= Vec3f(6, 6, 6);
  BOOST_CHECK_CLOSE_FRACTION(-2.58578644, d[0], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.0, d[1], 0.00001);
  BOOST_CHECK_CLOSE_FRACTION(-1.76393203, d[2], 0.00001);
}

BOOST_AUTO_TEST_SUITE_END()

// int main()
// {
//   Vec3f v3f(3.3, 2.2, -1.1);
//   Vec3d v3d(-5.778, 9.929393, 1.00000001);
//   Vector3<long double> v3ld(1.0, 1.5, 2.0);

//   auto test = v3f.dot(v3d);

//   std::cout
//     << "Hello, vectors!" << std::endl
//     << "Vec3f: " << v3f[0] << " " << v3f[1] << " " << v3f[2] << std::endl
//     << "Vec3d: " << v3d[0] << " " << v3d[1] << " " << v3d[2] << std::endl
//     << "Long double Vector3: " << v3ld[0] << " " << v3ld[1] << " " << v3ld[2] << std::endl
//     << "Test: " << typeid(v3f).name() << std::endl;

//   return EXIT_SUCCESS;
// }
