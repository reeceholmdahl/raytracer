#ifndef _BLINN_PHONG_SHADER_REECE_
#define _BLINN_PHONG_SHADER_REECE_

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