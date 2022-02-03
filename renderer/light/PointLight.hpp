#ifndef _POINT_LIGHT_REECE_
#define _POINT_LIGHT_REECE_

#include "Light.hpp"
#include "Vector3.hpp"

class PointLight : public Light
{
public:
  PointLight() = default;
  PointLight(const Vec3d &position, const Vec3f &intensity);
  virtual ~PointLight() {}

  Vec3d position() const;
  virtual Vec3f intensity() const;

private:
  Vec3d m_position;
  Vec3f m_intensity;
};

#endif