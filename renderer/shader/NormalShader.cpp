#include "NormalShader.hpp"

Vec3f NormalShader::apply(const HitStruct &hit) const
{
    return (Vec3f(1, 1, 1) + hit.normal) / 2;
}