#ifndef _SPHERE_REECE_
#define _SPHERE_REECE_

#include "Shape.hpp"
#include "Vector3.hpp"

class Sphere : public Shape
{
public:
  Sphere();
  Sphere(const Vec3d &position, const double radius);
  virtual ~Sphere() {}

  virtual bool closestHit(const Ray &r, const double tmin, const double tmax, double &t) const;
  virtual bool closestHit(const Ray &r) const;

  virtual Vec3d normal(const Vec3d &position) const;

private:
  Vec3d m_position;
  double m_radius;
};

#endif