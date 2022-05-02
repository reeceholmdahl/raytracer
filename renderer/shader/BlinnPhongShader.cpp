#include "BlinnPhongShader.hpp"
#include "Light.hpp"
#include "Scene.hpp"

BlinnPhongShader::BlinnPhongShader(const Vec3f& color, const Vec3f& specular,
                                   const double pexp)
  : LambertShader(color)
  , m_specular(specular)
  , m_pexp(pexp)
{
}

Vec3f
BlinnPhongShader::apply(const HitStruct& hit) const
{
  Vec3f color;
  for (Light* light : hit.scene->lights) {
    Ray toLight(hit.hitPoint(), light->position() - hit.hitPoint());

    HitStruct shadowHit(renderer::constants::VERY_SMALL, 1.0, hit.scene);
    if (!hit.scene->useShadows || !hit.scene->anyHit(toLight, shadowHit)) {
      auto lightDir = toLight.direction().unitize();

      color += m_diffuse * light->intensity() *
               std::max(0.0, hit.normal.dot(lightDir));

      auto halfVector(((-hit.ray.direction()).unitize() + lightDir).unitize());

      color += m_specular * light->intensity() *
               std::pow(std::max(0.0, hit.normal.dot(halfVector)), m_pexp);
    }
  }

  color += m_diffuse * m_ambient;
  // color.set(
  //     std::min(1.0f, color[0]),
  //     std::min(1.0f, color[1]),
  //     std::min(1.0f, color[2]));

  return color;
}