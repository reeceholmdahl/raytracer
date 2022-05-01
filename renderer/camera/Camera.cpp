#include "Camera.hpp"

Camera::Camera(const Vec3d& position, const Vec3d& viewDir,
               const double imagePlaneWidth, const double aspectRatio)
  : m_imagePlaneWidth(imagePlaneWidth)
  , m_imagePlaneHeight(imagePlaneWidth / aspectRatio)
  , m_basis(CoordSys(position, viewDir))
{
  left = -m_imagePlaneWidth / 2.;
  right = m_imagePlaneWidth / 2.;
  bottom = -m_imagePlaneHeight / 2.;
  top = m_imagePlaneHeight / 2.;
}