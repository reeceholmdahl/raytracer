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
    Ray toLight(hit.hitPoint(), light->position() - hit.hitPoint());

    HitStruct shadowHit(renderer::constants::VERY_SMALL, 1.0, hit.scene);
    if (!hit.scene->anyHit(toLight, shadowHit)) {
      color += m_diffuse * light->intensity() *
               std::max(0.0, hit.normal.dot(toLight.direction().unitize()));
    }
  }

  color += m_diffuse * m_ambient;

  return color;
}