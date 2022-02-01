#include "Camera.hpp"

Camera::Camera(const std::string &name, const CoordinateSys &basis)
  : m_name(name), m_basis(basis)
{
}

std::string Camera::name() const
{
  return m_name;
}

CoordinateSys Camera::basis() const
{
  return m_basis;
}