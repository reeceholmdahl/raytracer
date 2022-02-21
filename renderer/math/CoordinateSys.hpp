#ifndef _COORDINATE_SYS_REECE_
#define _COORDINATE_SYS_REECE_

#include "Vector3.hpp"

class CoordinateSys
{
public:
  CoordinateSys();                                                      // default gaze and position
  CoordinateSys(const Vec3d &position);                                 // default gaze, specified position
  CoordinateSys(const Vec3d &u, const const Vec3d &w);                  // default position, specified gaze
  CoordinateSys(const Vec3d &position, const Vec3d &u, const Vec3d &w); // specified position and gaze

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