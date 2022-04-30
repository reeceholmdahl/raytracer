#include "Camera.hpp"

Camera::Camera()
  : Camera(Vec3d(), Vec3d(0, 0, 1))
{
}

Camera::Camera(const Vec3d& position, const Vec3d& viewDir,
               const double imagePlaneWidth, const double aspectRatio)
  : m_imagePlaneWidth(imagePlaneWidth)
  , m_imagePlaneHeight(imagePlaneWidth / aspectRatio)
  , m_basis(CoordSys(position, viewDir))
{
}

CoordSys
Camera::basis() const
{
  return m_basis;
}

double
Camera::imagePlaneWidth() const
{
  return m_imagePlaneWidth;
}

double
Camera::imagePlaneHeight() const
{
  return m_imagePlaneHeight;
}

void
Camera::setImagePixels(const size_t x, const size_t y)
{
  m_pixelsX = x;
  m_pixelsY = y;
}