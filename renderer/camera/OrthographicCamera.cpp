#include "OrthographicCamera.hpp"

// OrthographicCamera::OrthographicCamera()
//     : OrthographicCamera(Vec3d(), Vec3d())
// {
// }

OrthographicCamera::OrthographicCamera(const Vec3d& position,
                                       const Vec3d& viewDir,
                                       const double imagePlaneWidth,
                                       const double aspectRatio)
  : Camera(position, viewDir, imagePlaneWidth, aspectRatio)
{
}

Ray
OrthographicCamera::generateRay(const size_t i, const size_t j) const
{

  double u, v;
  genUV(u, v, i, j);

  Vec3d origin(Vec3d(u, v, 0) + m_basis.position()), direction(0, 0, -1);

  Ray ray(origin, direction);

  return ray;
}