#include "Shape.hpp"

Shape::Shape(Shader *shaderPtr)
    : m_shaderPtr(shaderPtr)
{
}

void Shape::setShader(Shader *shaderPtr)
{
    m_shaderPtr = shaderPtr;
}

Shader *Shape::getShader() const
{
    return m_shaderPtr;
}