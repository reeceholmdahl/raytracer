#ifndef RENDERER_LIGHT_POINT_LIGHT_H_
#define RENDERER_LIGHT_POINT_LIGHT_H_

#include "Light.hpp"
#include "Vector3.hpp"

class PointLight : public Light
{
public:
  inline PointLight(const Vec3d& position, const Vec3f& intensity)
    : m_position(position)
    , m_intensity(intensity)
  {
  }
  virtual ~PointLight() {}

  inline virtual const Vec3d& position() const { return m_position; }

  inline virtual const Vec3f& intensity() const { return m_intensity; }

private:
  Vec3d m_position;
  Vec3f m_intensity;
};

#endif