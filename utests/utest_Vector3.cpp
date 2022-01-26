#include <iostream>

// First test is if this will compile with including Vector3
#include "Vector3.h"

int main()
{
  Vec3f v3f(3.3, 2.2, -1.1);
  Vec3d v3d(-5.778, 9.929393, 1.00000001);
  Vector3<long double> v3ld(1.0, 1.5, 2.0);

  //   auto test = v3f.dot(v3d);

  std::cout
    << "Hello, vectors!" << std::endl
    << "Vec3f: " << v3f[0] << " " << v3f[1] << " " << v3f[2] << std::endl
    << "Vec3d: " << v3d[0] << " " << v3d[1] << " " << v3d[2] << std::endl
    << "Long double Vector3: " << v3ld[0] << " " << v3ld[1] << " " << v3ld[2] << std::endl;
  return EXIT_SUCCESS;
}
