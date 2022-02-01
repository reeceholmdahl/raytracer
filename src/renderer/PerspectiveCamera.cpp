#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(const std::string &name, const CoordinateSys &basis, const double focalLength)
  : Camera(name, basis), m_focalLength(focalLength)
{
}

PerspectiveCamera::PerspectiveCamera(const std::string &name, const CoordinateSys &basis, const size_t pixels_x, const size_t pixels_y, const double image_w, const double image_h)
  : Camera(name, basis, pixels_x, pixels_y, image_w, image_h)
{
}

Ray PerspectiveCamera::generateRay(const size_t i, const size_t j) const
{
  // Can be calculated on position change, image size change, or framebuffer change
  auto l = -image_w() / 2;
  auto r = image_w() / 2;
  auto b = -image_h() / 2;
  auto t = image_h() / 2;

  auto u = l + (r - l) * (i + 0.5) / pixels_x();
  auto v = b + (t - b) * (j + 0.5) / pixels_y();

  Vec3d origin, direction(u, v, -m_focalLength);

  Ray ray(basis().toGlobal(origin), basis().toGlobal(direction));

  return ray;
}