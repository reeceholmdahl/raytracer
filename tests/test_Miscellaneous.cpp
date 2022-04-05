#include <iostream>

#include "renderer.hpp"
#include "Vector3.hpp"
#include "CoordSys.hpp"
#include "Sphere.hpp"

using namespace renderer;

int main()
{
  Vec3d u(1, 1, 0), v(-1, 1, 0);
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

  CoordSys basis(Vec3d(), u, w);

  Vec3d a(0.5, 0.5, 0);

  std::cout << "a_basis: " << basis.toGlobal(a) << std::endl;

  return 0;
}