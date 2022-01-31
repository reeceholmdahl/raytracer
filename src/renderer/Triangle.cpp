#include "Triangle.hpp"

#include "Vector3.hpp"
#include "Ray.hpp"

Triangle::Triangle(const Vec3d &a, const Vec3d &b, const Vec3d &c)
  : m_a(a), m_b(b), m_c(c)
{
}

bool Triangle::closestHit(const Ray &r) const
{
  return false;
}