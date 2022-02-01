#ifndef _SHAPE_REECE_
#define _SHAPE_REECE_

#include "Ray.hpp"

class Shape
{
public:
  Shape() = default;
  virtual ~Shape() {}

  virtual bool closestHit(const Ray &r, const double tmin, const double tmax, double &t) const = 0;
  virtual bool closestHit(const Ray &r) const = 0;
};

#endif