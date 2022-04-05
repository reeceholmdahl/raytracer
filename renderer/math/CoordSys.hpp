#ifndef RENDERER_MATH_COORDINATE_SYS_H_
#define RENDERER_MATH_COORDINATE_SYS_H_

#include "Vector3.hpp"

class CoordSys
{
public:
  CoordSys();                                                      // default gaze and position
  CoordSys(const Vec3d &position);                                 // default gaze, specified position
  CoordSys(const Vec3d &u, const Vec3d &w);                        // default position, specified gaze
  CoordSys(const Vec3d &position, const Vec3d &u, const Vec3d &w); // specified position and gaze

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