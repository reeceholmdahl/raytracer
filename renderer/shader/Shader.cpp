#include "Shader.hpp"
#include "NullShader.hpp"

const Vec3f Shader::DEFAULT_AMBIENT = Vec3f(0.0, 0.0, 0.0);

Shader *Shader::NULL_SHADER = new NullShader();

Shader::Shader(const Vec3f &ambient)
    : m_ambient(ambient)
{
}

const Vec3f &Shader::ambient() const
{
    return m_ambient;
}