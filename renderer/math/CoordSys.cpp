#include <cassert>

#include "CoordSys.hpp"

CoordSys::CoordSys()
    : CoordSys(Vec3d(), Vec3d(0, 0, -1))
{
}

CoordSys::CoordSys(const Vec3d &position, const Vec3d &viewDir)
    : m_position(position)
{
  // m_u = v.cross(w);

  m_w = -viewDir;
  Vec3d temp(m_w);
  auto x = std::abs(m_w[0]);
  auto y = std::abs(m_w[1]);
  auto z = std::abs(m_w[2]);

  if (z <= x && z <= y)
  {
    temp[2] = 1;
  }
  else if (y <= x)
  {
    temp[1] = 1;
  }
  else
  {
    temp[0] = 1;
  }

  // temp[1] = 1;

  // temp = temp.unitize();

  // auto smaller = std::min(x, y);
  // auto smallest = std::min(smaller, z);
  // if (smallest == x)
  // {
  //   temp[0] = 1;
  // }
  // else if (smallest == z)
  // {
  //   temp[1] = 1;
  // }
  // else
  // {
  //   temp[2] = 1;
  // }
  // 11 bad
  // 12 bad
  // 21 bad
  m_u = temp.cross(m_w);
  // m_u = m_w.cross(temp);

  m_v = m_w.cross(m_u);
  // m_v = m_u.cross(m_w);

  m_u = m_u.unitize();
  m_v = m_v.unitize();
  m_w = m_w.unitize();

  std::cerr << "View dir: " << viewDir << std::endl;
  std::cerr << "W: " << m_w << std::endl;
  std::cout << "temp: " << temp << std::endl;
  std::cerr << "U: " << m_u << std::endl;
  std::cerr << "V: " << m_v << std::endl;

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