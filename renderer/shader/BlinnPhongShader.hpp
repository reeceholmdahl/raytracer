#ifndef RENDERER_SHADER_BLINN_PHONG_SHADER_H_
#define RENDERER_SHADER_BLINN_PHONG_SHADER_H_

#include "LambertShader.hpp"
#include "Vector3.hpp"
#include "HitStruct.hpp"

class BlinnPhongShader : public LambertShader
{
public:
    BlinnPhongShader() = default;
    BlinnPhongShader(const Vec3f &ambient, const Vec3f &diffuse, const Vec3f &specular, const double pexp);
    virtual ~BlinnPhongShader() {}

    virtual Vec3f apply(const HitStruct &h) const;

protected:
    Vec3f m_specular;
    double m_pexp;
};

#endif