#include "PerspectiveCamera.hpp"

Ray
PerspectiveCamera::generateRay(const size_t i,
                               const size_t j,
                               const double di,
                               const double dj) const
{

  double u, v;
  genUV(u, v, i, j, di, dj);

  Vec3d origin(m_basis.position()),
    direction(m_basis.u() * u + m_basis.v() * v + m_basis.w() * -m_focalLength);

  Ray ray(origin, direction);

  return ray;
}