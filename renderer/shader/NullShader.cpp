#include "NullShader.hpp"

NullShader::NullShader(const Vec3f &ambient)
    : Shader(ambient)
{
}

Vec3f NullShader::apply(const HitStruct &hit) const
{
    return Vec3f(1, 0, 1);
}