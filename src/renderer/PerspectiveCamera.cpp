#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(const std::string &name, const CoordinateSys &basis, const double focalLength)
  : Camera(name, basis), m_focalLength(focalLength)
{
}

Ray PerspectiveCamera::generateRay(const size_t i, const size_t j) const
{
  // Can be calculated on position change, image size change, or framebuffer change
  auto l = -m_image_w / 2;
  auto r = m_image_w / 2;
  auto b = -m_image_h / 2;
  auto t = m_image_h / 2;

  auto u = l + (r - l) * (i + 0.5) / m_pixels_x;
  auto v = b + (t - b) * (j + 0.5) / m_pixels_y;

  Vec3d origin, direction(u, v, -m_focalLength);

  Ray ray(basis().toGlobal(origin), basis().toGlobal(direction));

  return ray;
}