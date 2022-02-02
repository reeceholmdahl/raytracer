#include "CoordinateSys.hpp"

const CoordinateSys CoordinateSys::GLOBAL = CoordinateSys(Vec3d(), Vec3d(1, 0, 0), Vec3d(0, 1, 0), Vec3d(0, 0, 1));
const CoordinateSys CoordinateSys::CAMERA_DEFAULT = CoordinateSys(Vec3d(), Vec3d(1, 0, 0), Vec3d(0, 1, 0), Vec3d(0, 0, -1));

CoordinateSys::CoordinateSys(const Vec3d &position, const Vec3d &u, const Vec3d &v, const Vec3d &w)
  : m_position(position), m_u(u), m_v(v), m_w(w)
{
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