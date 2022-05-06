#include "OrthographicCamera.hpp"

Ray
OrthographicCamera::generateRay(const size_t i,
                                const size_t j,
                                const double di,
                                const double dj) const
{

  double u, v;
  genUV(u, v, i, j, di, dj);

  Vec3d origin(Vec3d(u, v, 0) + m_basis.position()), direction(0, 0, -1);

  Ray ray(origin, direction);

  return ray;
}