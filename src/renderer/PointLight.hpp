#ifndef _POINT_LIGHT_REECE_
#define _POINT_LIGHT_REECE_

#include "Light.hpp"
#include "Vector3.hpp"

class PointLight : public Light
{
public:
  PointLight();

private:
  Vec3d m_position;
  Vec3f m_intensity;
};

#endif