#include "NormalShader.hpp"

NormalShader::NormalShader(const Vec3f &ambient)
    : Shader(ambient)
{
}

Vec3f NormalShader::apply(const HitStruct &hit) const
{
    return (Vec3f(1, 1, 1) + hit.normal) / 2;
}