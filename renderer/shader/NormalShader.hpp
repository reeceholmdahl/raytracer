#ifndef _NORMAL_SHADER_REECE_
#define _NORMAL_SHADER_REECE_

#include "Vector3.hpp"
#include "HitStruct.hpp"

class NormalShader : public Shader
{
public:
    NormalShader() = default;
    NormalShader(const Vec3f &ambient);
    virtual ~NormalShader() {}

    virtual Vec3f apply(const HitStruct &h) const;
};

#endif