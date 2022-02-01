#ifndef _TRIANGLE_REECE_
#define _TRIANGLE_REECE_

#include "Vector3.hpp"
#include "Shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const Vec3d &a, const Vec3d &b, const Vec3d &c);

  virtual bool closestHit(const Ray &r, const double tmin, const double tmax, double &t) const;
  virtual bool closestHit(const Ray &r) const;

private:
  Vec3d m_a, m_b, m_c;
};

#endif