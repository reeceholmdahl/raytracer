#include "DiffuseShader.hpp"

DiffuseShader::DiffuseShader(const Vec3f& color)
  : m_color(color)
{
}

Vec3f
DiffuseShader::apply(const HitStruct& hit) const
{
  return m_color;
}