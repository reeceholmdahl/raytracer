#ifndef RENDERER_MATH_RAY_H_
#define RENDERER_MATH_RAY_H_

#include "Vector3.hpp"

class Ray
{
public:
  Ray() = default;
  Ray(const Ray& r);
  Ray(const Vec3d& origin, const Vec3d& direction);

  Vec3d origin() const;
  Vec3d direction() const;

  Vec3d point(const double t) const;

private:
  Vec3d m_origin, m_direction;
};

#endif