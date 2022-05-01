#include "PerspectiveCamera.hpp"
#include <iostream>

PerspectiveCamera::PerspectiveCamera(const Vec3d& position,
                                     const Vec3d& viewDir,
                                     const double focalLength,
                                     const double imagePlaneWidth,
                                     const double aspectRatio)
  : Camera(position, viewDir, imagePlaneWidth, aspectRatio)
  , m_focalLength(focalLength)
{
}

Ray
PerspectiveCamera::generateRay(const size_t i, const size_t j) const
{

  double u, v;
  genUV(u, v, i, j);

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