#ifndef _COORDINATE_SYS_REECE_
#define _COORDINATE_SYS_REECE_

#include "Vector3.hpp"

class CoordinateSys
{
public:
  static const CoordinateSys GLOBAL, CAMERA_DEFAULT;

  CoordinateSys(const Vec3d &position, const Vec3d &u, const Vec3d &v, const Vec3d &w);

  Vec3d toLocal(const Vec3d &global) const;
  Vec3d toGlobal(const Vec3d &local) const;
  Vec3d position() const;
  Vec3d u() const;
  Vec3d v() const;
  Vec3d w() const;

private:
  Vec3d m_position, m_u, m_v, m_w;
};

#endif