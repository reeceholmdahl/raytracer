#include "Ray.hpp"

#include "Vector3.hpp"

Ray::Ray(const Vec3d &origin, const Vec3d &direction)
  : m_origin(origin), m_direction(direction)
{
}