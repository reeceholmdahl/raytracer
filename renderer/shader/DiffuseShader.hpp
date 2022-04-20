#ifndef RENDERER_SHADER_DIFFUSE_SHADER_H_
#define RENDERER_SHADER_DIFFUSE_SHADER_H_

#include "Vector3.hpp"
#include "HitStruct.hpp"

class DiffuseShader : public Shader
{
public:
    DiffuseShader() = default;
    DiffuseShader(const Vec3f &ambient, const Vec3f &color);
    virtual ~DiffuseShader() {}

    virtual Vec3f apply(const HitStruct &h) const;

private:
    Vec3f m_color;
};

#endif