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
