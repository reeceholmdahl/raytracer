#ifndef RENDERER_LIGHT_LIGHT_H_
#define RENDERER_LIGHT_LIGHT_H_

#include "Vector3.hpp"

class Light
{
public:
  Light() = default;
  virtual ~Light() {}

  virtual const Vec3f& intensity() const = 0;
  virtual const Vec3d& position() const = 0;
};

#endif