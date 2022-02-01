#include <iostream>

#include "Vector3.hpp"
#include "CoordinateSys.hpp"

int main()
{
  //   Vec3d u(1, 1, 1), v(-1, 0, 1);
  Vec3d u, v, p;
  std::cout << "Input u: ";
  std::cin >> u;
  std::cout << "Input v: ";
  std::cin >> v;
  std::cout << "Input position of basis: ";
  std::cin >> p;
  u = u.unitize();
  v = v.unitize();
  Vec3d w = u.cross(v);
  auto udotv = u.dot(v);
  auto udotw = u.dot(w);
  auto vdotw = v.dot(w);
  std::cout << "u: " << u << " |u| = " << u.magnitude() << std::endl
            << "v: " << v << " |v| = " << v.magnitude() << std::endl
            << "w: " << w << " |w| = " << w.magnitude() << std::endl
            << "udotv: " << udotv << std::endl
            << "udotw: " << udotw << std::endl
            << "vdotw: " << vdotw << std::endl;

  CoordinateSys cs(p, u, v, w);

  Vec3d test;
  std::cout << "Input test vector: ";
  std::cin >> test;
  std::cout << "test: " << test << " |test| = " << test.magnitude() << std::endl;

  auto inCS = cs.toLocal(test);

  std::cout << "in uvw: " << inCS << std::endl;

  auto inG = cs.toGlobal(inCS);

  std::cout << "in xyz: " << inG << std::endl;

  //   Vec3d testLocalToGlobal, testGlobalToLocal;
  //   testLocalToGlobal = Vec3d(test.dot(u), test.dot(v), test.dot(w)) + p;
  //   std::cout << "(t_g) test from local to global: " << testLocalToGlobal << "|t_g| = " << testLocalToGlobal.magnitude() << std::endl;

  //   Vec3d temp(test - p);
  //   testGlobalToLocal = Vec3d(temp.dot(u), temp.dot(v), temp.dot(w));
  //   std::cout << "(t_l) test from global to local: " << testGlobalToLocal << "|t_l| = " << testGlobalToLocal.magnitude() << std::endl;

  return 0;
}