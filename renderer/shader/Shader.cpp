#include "Shader.hpp"

Shader::Shader(const Vec3f &ambient)
    : m_ambient(ambient)
{
}

const Vec3f &Shader::ambient() const
{
    return m_ambient;
}