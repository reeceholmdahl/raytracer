#include "LambertShader.hpp"

LambertShader::LambertShader(const Vec3f &ambient, const Vec3f &color)
    : Shader(ambient), m_diffuse(color)
{
}

Vec3f LambertShader::apply(const HitStruct &hit) const
{
    Vec3f color;
    for (Light *light : hit.m_lights)
    {
        auto hitToLight((light->position() - hit.hitPoint()).unitize());
        auto normal(hit.shape->normal(hit.hitPoint()));

        color += m_diffuse * light->intensity() * std::max(0.0, normal.dot(hitToLight));
    }

    color += m_diffuse * m_ambient;
    // color.set(
    //     std::min(1.0f, color[0]),
    //     std::min(1.0f, color[1]),
    //     std::min(1.0f, color[2]));

    return color;
}