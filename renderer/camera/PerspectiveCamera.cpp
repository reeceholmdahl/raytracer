#include "PerspectiveCamera.hpp"

inline Ray
PerspectiveCamera::generateRay(const size_t i,
                               const size_t j,
                               const double di,
                               const double dj) const
{

  double u, v;
  genUV(u, v, i, j, di, dj);

  Vec3d origin(m_basis.position()),
    direction(m_basis.u() * u + m_basis.v() * v + m_basis.w() * -m_focalLength);
  // direction.set(direction.dot(basis().u()), direction.dot(basis().v()),
  // direction.dot(basis().w()));

  // std::cout << direction << std::endl;

  // Ray ray(basis().toGlobal(origin), basis().toGlobal(direction));
  Ray ray(origin, direction);
  // Ray ray(basis().toGlobal(origin), direction);
  // std::cout << direction << std::endl;

  return ray;
}