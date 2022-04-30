#ifndef RENDERER_LIGHT_POINT_LIGHT_H_
#define RENDERER_LIGHT_POINT_LIGHT_H_

#include "Light.hpp"
#include "Vector3.hpp"

class PointLight : public Light
{
public:
  PointLight() = default;
  PointLight(const Vec3d& position, const Vec3f& intensity);
  virtual ~PointLight() {}

  virtual Vec3d position() const;
  virtual Vec3f intensity() const;

private:
  Vec3d m_position;
  Vec3f m_intensity;
};

#endif