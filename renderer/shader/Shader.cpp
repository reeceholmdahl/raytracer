#include "Shader.hpp"

const Vec3f Shader::DEFAULT_AMBIENT = Vec3f(0.0, 0.0, 0.0);

Shader::Shader(const std::string &name, const Vec3f &ambient)
    : m_name(name), m_ambient(ambient)
{
}

const std::string &Shader::name() const
{
    return m_name;
}

const Vec3f &Shader::ambient() const
{
    return m_ambient;
}