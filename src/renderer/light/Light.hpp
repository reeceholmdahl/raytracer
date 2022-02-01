#ifndef _LIGHT_REECE_
#define _LIGHT_REECE_

#include "Vector3.hpp"

class Light
{
public:
  Light() = default;
  virtual ~Light() {}

  virtual Vec3f intensity() const = 0;
};

#endif