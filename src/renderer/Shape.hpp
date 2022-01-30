#ifndef _SHAPE_REECE_
#define _SHAPE_REECE_

#include "Ray.hpp"

class Shape
{
public:
  Shape();
  virtual bool closestHit(const Ray &r) = 0;
};

#endif