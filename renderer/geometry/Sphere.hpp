#ifndef RENDERER_GEOMETRY_SPHERE_H_
#define RENDERER_GEOMETRY_SPHERE_H_

#include "Shape.hpp"
#include "HitStruct.hpp"
#include "Vector3.hpp"

class Sphere : public Shape
{
public:
  Sphere();
  Sphere(const Vec3d &position, const double radius);
  virtual ~Sphere() {}

  virtual bool closestHit(const Ray &r, const double tmin, const double tmax, HitStruct &hit) const;

  virtual Vec3d normal(const Vec3d &position) const;

private:
  Vec3d m_position;
  double m_radius;
};

#endif