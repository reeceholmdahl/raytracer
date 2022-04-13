#include <cassert>

#include "CoordSys.hpp"

CoordSys::CoordSys()
    : CoordSys(Vec3d(), Vec3d(0, 0, -1))
{
}

CoordSys::CoordSys(const Vec3d &position, const Vec3d &gazeDir)
    : m_position(position)
{
  // m_u = v.cross(w);

  Vec3d up(0, 1, 0);

  m_w = (-gazeDir).unitize();
  m_u = up.cross(m_w).unitize();
  if (m_u.magnitude() != 1.)
  {
    std::cerr << "Having to use another temp up vector" << std::endl;

    up = m_w;
    auto x = std::abs(m_w[0]);
    auto y = std::abs(m_w[1]);
    auto z = std::abs(m_w[2]);
    auto smaller = std::min(x, y);
    auto smallest = std::min(smaller, z);
    if (smallest == x)
    {
      up[0] = 1;
    }
    else if (smallest == z)
    {
      up[1] = 1;
    }
    else
    {
      up[2] = 1;
    }

    m_u = up.cross(m_w).unitize();
  }
  m_v = m_w.cross(m_u);

  std::cerr << "uxv: " << m_u.cross(m_v) << " w: " << m_w << std::endl;

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