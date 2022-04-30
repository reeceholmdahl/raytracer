#include "PointLight.hpp"

#include "Vector3.hpp"

PointLight::PointLight(const Vec3d& position, const Vec3f& intensity)
  : m_position(position)
  , m_intensity(intensity)
{
}

Vec3d
PointLight::position() const
{
  return m_position;
}

Vec3f
PointLight::intensity() const
{
  return m_intensity;
}