#include <cassert>

#include "CoordSys.hpp"

#define DEBUG_COORDSYS 0

CoordSys::CoordSys(const Vec3d& position, const Vec3d& viewDir)
  : m_position(position)
{
  m_w = -(viewDir.unitize());

  Vec3d tempUp(0, 1, 0);
  auto tdotw = tempUp.dot(m_w);

  if (tdotw == 1 || tdotw == -1) {

    tempUp = m_w;

    auto x = std::abs(tempUp[0]);
    auto y = std::abs(tempUp[1]);
    auto z = std::abs(tempUp[2]);

    if (x <= y && x <= z) {
      tempUp[0] = 1;
    } else if (y <= x) {
      tempUp[1] = 1;
    } else {
      tempUp[2] = 1;
    }
  }

  m_u = tempUp.cross(m_w);
  m_v = m_w.cross(m_u);

  m_u = m_u.unitize();
  m_v = m_v.unitize();

#if DEBUG_COORDSYS
  std::cerr << "U: " << m_u << std::endl;
  std::cerr << "V: " << m_v << std::endl;
  std::cerr << "W: " << m_w << std::endl;
  std::cerr << "View dir: " << viewDir << std::endl;
  std::cout << "Temp up: " << tempUp << std::endl;

  assert(m_w.dot(m_u) == 0.0);
  assert(m_w.dot(m_v) == 0.0);
  assert(m_u.dot(m_v) == 0.0);
  assert(m_u.magnitude() == 1.0);
  assert(m_v.magnitude() == 1.0);
  assert(m_w.magnitude() == 1.0);
#endif
}

Vec3d
CoordSys::toLocal(const Vec3d& global) const
{
  Vec3d temp(global - m_position);
  return Vec3d(temp.dot(m_u), temp.dot(m_v), temp.dot(m_w));
}

Vec3d
CoordSys::toGlobal(const Vec3d& local) const
{
  return Vec3d(local.dot(m_u), local.dot(m_v), local.dot(m_w)) + m_position;
}