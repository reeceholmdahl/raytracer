#include "LambertShader.hpp"
#include "Light.hpp"
#include "Scene.hpp"

LambertShader::LambertShader(const Vec3f& color)
  : m_diffuse(color)
{
}

Vec3f
LambertShader::apply(const HitStruct& hit) const
{
  Vec3f color;
  for (Light* light : hit.scene->lights) {
    auto hitToLight((light->position() - hit.hitPoint()).unitize());

    color += m_diffuse * light->intensity() *
             std::max(0.0, hit.normal.dot(hitToLight));
  }

  color += m_diffuse * m_ambient;

  return color;
}