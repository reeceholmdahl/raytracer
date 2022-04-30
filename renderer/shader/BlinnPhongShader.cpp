#include "BlinnPhongShader.hpp"

BlinnPhongShader::BlinnPhongShader(const Vec3f &color, const Vec3f &specular, const double pexp)
    : LambertShader(color), m_specular(specular), m_pexp(pexp)
{
}

Vec3f BlinnPhongShader::apply(const HitStruct &hit) const
{
    Vec3f color;
    for (Light *light : *hit.lights)
    {
        auto hitToLight((light->position() - hit.hitPoint()).unitize());

        color += m_diffuse * light->intensity() * std::max(0.0, hit.normal.dot(hitToLight));

        auto halfVector(((-hit.ray.direction()).unitize() + hitToLight).unitize());

        color += m_specular * light->intensity() * std::pow(std::max(0.0, hit.normal.dot(halfVector)), m_pexp);
    }

    color += m_diffuse * m_ambient;
    // color.set(
    //     std::min(1.0f, color[0]),
    //     std::min(1.0f, color[1]),
    //     std::min(1.0f, color[2]));

    return color;
}