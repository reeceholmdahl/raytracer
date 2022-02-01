#ifndef _RAY_REECE_
#define _RAY_REECE_

#include "Vector3.hpp"

class Ray
{
public:
  Ray() = default;
  Ray(const Vec3d &origin, const Vec3d &direction);

  Vec3d origin() const;
  Vec3d direction() const;

private:
  Vec3d m_origin, m_direction;
};

#endif