#include "Camera.hpp"

Camera::Camera(const std::string &name, const Vec3d &position, const CoordinateSys &basis)
  : m_name(name), m_position(position), m_basis(basis)
{
}

std::string Camera::name() const
{
  return m_name;
}

Vec3d Camera::position() const
{
  return m_position;
}

CoordinateSys Camera::basis() const
{
  return m_basis;
}