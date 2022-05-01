#include "Camera.hpp"

Camera::Camera(const Vec3d& position, const Vec3d& viewDir,
               const double imagePlaneWidth, const double aspectRatio)
  : m_imagePlaneWidth(imagePlaneWidth)
  , m_imagePlaneHeight(imagePlaneWidth / aspectRatio)
  , m_basis(CoordSys(position, viewDir))
{
}