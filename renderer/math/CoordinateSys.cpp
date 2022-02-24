#include <cassert>

#include "CoordinateSys.hpp"

CoordinateSys::CoordinateSys()
    : CoordinateSys(Vec3d(), Vec3d(0, 1, 0), Vec3d(0, 0, -1))
{
}

CoordinateSys::CoordinateSys(const Vec3d &position)
    : CoordinateSys(position, Vec3d(0, 1, 0), Vec3d(0, 0, -1))
{
}

CoordinateSys::CoordinateSys(const Vec3d &up, const Vec3d &view)
    : CoordinateSys(Vec3d(), up, view)
{
}

CoordinateSys::CoordinateSys(const Vec3d &position, const Vec3d &up, const Vec3d &view)
    : m_position(position)
{
  // m_u = v.cross(w);

  m_w = (-view).unitize();
  m_u = up.cross(m_w).unitize();
  m_v = m_w.cross(m_u);

  assert(m_w.dot(m_u) == 0.0);
  assert(m_w.dot(m_v) == 0.0);
  assert(m_u.dot(m_v) == 0.0);
  assert(m_u.magnitude() == 1.0);
  assert(m_v.magnitude() == 1.0);
  assert(m_w.magnitude() == 1.0);
}

Vec3d CoordinateSys::toLocal(const Vec3d &global) const
{
  Vec3d temp(global - m_position);
  return Vec3d(temp.dot(m_u), temp.dot(m_v), temp.dot(m_w));
}

Vec3d CoordinateSys::toGlobal(const Vec3d &local) const
{
  return Vec3d(local.dot(m_u), local.dot(m_v), local.dot(m_w)) + m_position;
}

Vec3d CoordinateSys::position() const
{
  return m_position;
}

Vec3d CoordinateSys::u() const
{
  return m_u;
}

Vec3d CoordinateSys::v() const
{
  return m_v;
}

Vec3d CoordinateSys::w() const
{
  return m_w;
}