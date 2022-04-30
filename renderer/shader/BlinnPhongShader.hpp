#ifndef RENDERER_SHADER_BLINN_PHONG_SHADER_H_
#define RENDERER_SHADER_BLINN_PHONG_SHADER_H_

#include "LambertShader.hpp"
#include "Vector3.hpp"
#include "HitStruct.hpp"

class BlinnPhongShader : public LambertShader
{
public:
    BlinnPhongShader(
        const Vec3f &diffuse = renderer::constants::DEFAULT_DIFFUSE,
        const Vec3f &specular = renderer::constants::DEFAULT_SPECULAR,
        const double pexp = renderer::constants::DEFAULT_PHONG_EXP);
    virtual ~BlinnPhongShader() {}

    virtual Vec3f apply(const HitStruct &h) const;

protected:
    Vec3f m_specular;
    double m_pexp;
};

#endif