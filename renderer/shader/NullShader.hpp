#ifndef RENDERER_SHADER_NULL_SHADER_H_
#define RENDERER_SHADER_NULL_SHADER_H_

#include "Vector3.hpp"
#include "HitStruct.hpp"

class NullShader : public Shader
{
public:
    NullShader() = default;
    NullShader(const Vec3f &ambient);
    virtual ~NullShader() {}

    virtual Vec3f apply(const HitStruct &h) const;
};

#endif