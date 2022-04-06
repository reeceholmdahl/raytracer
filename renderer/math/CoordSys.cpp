#include <cassert>

#include "CoordSys.hpp"

CoordSys::CoordSys()
    : CoordSys(Vec3d(), Vec3d(0, 0, 1))
{
}

CoordSys::CoordSys(const Vec3d &position, const Vec3d &view)
    : m_position(position)
{
  // m_u = v.cross(w);

  Vec3d up(0, 1, 0);

  m_w = (view).unitize();
  m_u = up.cross(m_w).unitize();
  if (m_u.magnitude() != 1.)
  {
    std::cout << "Having to use another temp up vector" << std::endl;
    up = Vec3d(0, 0, -1);
    m_u = up.cross(m_w);
  }
  m_v = m_w.cross(m_u);

  assert(m_w.dot(m_u) == 0.0);
  assert(m_w.dot(m_v) == 0.0);
  assert(m_u.dot(m_v) == 0.0);
  assert(m_u.magnitude() == 1.0);
  assert(m_v.magnitude() == 1.0);
  assert(m_w.magnitude() == 1.0);
}

Vec3d CoordSys::toLocal(const Vec3d &global) const
{
  Vec3d temp(global - m_position);
  return Vec3d(temp.dot(m_u), temp.dot(m_v), temp.dot(m_w));
}

Vec3d CoordSys::toGlobal(const Vec3d &local) const
{
  return Vec3d(local.dot(m_u), local.dot(m_v), local.dot(m_w)) + m_position;
}

Vec3d CoordSys::position() const
{
  return m_position;
}

Vec3d CoordSys::u() const
{
  return m_u;
}

Vec3d CoordSys::v() const
{
  return m_v;
}

Vec3d CoordSys::w() const
{
  return m_w;
}