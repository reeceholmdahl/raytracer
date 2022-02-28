#include "Ray.hpp"

Ray::Ray(const Ray &r)
    : Ray(r.m_origin, r.m_direction)
{
}

Ray::Ray(const Vec3d &origin, const Vec3d &direction)
    : m_origin(origin), m_direction(direction)
{
}

Vec3d Ray::origin() const
{
  return m_origin;
}

Vec3d Ray::direction() const
{
  return m_direction;
}

Vec3d Ray::point(const double t) const
{
  return m_origin + (m_direction * t);
}