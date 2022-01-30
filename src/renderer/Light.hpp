#ifndef _LIGHT_REECE_
#define _LIGHT_REECE_

#include "Vector3.hpp"

class Light
{
public:
  Light();

private:
  unsigned int intensity;
  Vec3d position;
};

#endif