#ifndef _NULL_SHADER_REECE_
#define _NULL_SHADER_REECE_

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