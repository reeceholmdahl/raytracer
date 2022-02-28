#include "LambertShader.hpp"

LambertShader::LambertShader(const Vec3f &ambient, const Vec3f &color)
    : Shader(ambient), m_color(color)
{
}

Vec3f LambertShader::apply(const HitStruct &hit) const
{
    Vec3f intensity;
    for (Light *light : *(hit.lights))
    {
        auto hitToLight((light->position() - hit.hitPoint()).unitize());
        auto normal(hit.shape->normal(hit.hitPoint()));

        intensity += light->intensity() * std::max(0.0, normal.dot(hitToLight));
    }

    auto color = m_color * intensity;
    color.set(
        std::min(1.0f, color[0]),
        std::min(1.0f, color[1]),
        std::min(1.0f, color[2]));

    return color;
}