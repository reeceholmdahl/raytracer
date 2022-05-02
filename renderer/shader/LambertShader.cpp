#include <iostream>

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

    HitStruct shadowHit(renderer::constants::VERY_SMALL, 1, hit.scene);
    if (!hit.scene->anyHit(toLight, shadowHit)) {
      color += m_diffuse * light->intensity() *
               std::max(0.0, hit.normal.dot(toLight.direction().unitize()));
      // std::cerr << "coloring something?" << std::endl;
    } else {
      if (shadowHit.shape->name() == "ceil") {
        // std::cerr << "err hit t: " << shadowHit.t << std::endl;
      }
      // std::cerr << "name: " << shadowHit.shape->name() << std::endl;
    }
  }

  color += m_diffuse * m_ambient;

  return color;
}