#ifndef RENDERER_MATH_COORDSYS_H_
#define RENDERER_MATH_COORDSYS_H_

#include "Vector3.hpp"
#include "Constants.h"

class CoordSys
{
public:
  CoordSys() = delete;
  CoordSys(
    const Vec3d& position,
    const Vec3d& viewDir); // default gaze, specified positionosition and gaze

  Vec3d toLocal(const Vec3d& global) const;
  Vec3d toGlobal(const Vec3d& local) const;

  inline const Vec3d& position() const { return m_position; }
  inline const Vec3d& u() const { return m_u; }
  inline const Vec3d& v() const { return m_v; }
  inline const Vec3d& w() const { return m_w; }

private:
  Vec3d m_position, m_u, m_v, m_w;
};

#endif