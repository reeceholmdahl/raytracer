#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(const std::string &name, const CoordinateSys &basis)
  : Camera(name, basis)
{
}

Ray OrthographicCamera::generateRay(const size_t i, const size_t j) const
{
  // Can be calculated on position change, image size change, or framebuffer change
  auto l = -m_image_w / 2;
  auto r = m_image_w / 2;
  auto b = -m_image_h / 2;
  auto t = m_image_h / 2;

  auto u = l + (r - l) * (i + 0.5) / m_pixels_x;
  auto v = b + (t - b) * (j + 0.5) / m_pixels_y;

  Vec3d origin(u, v, 0);

  Ray ray(basis().toGlobal(origin), basis().toGlobal(Vec3d(0, 0, -1)));

  return ray;
}