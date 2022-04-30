#ifndef RENDERER_SHADER_LAMBERT_SHADER_H_
#define RENDERER_SHADER_LAMBERT_SHADER_H_

#include "Vector3.hpp"
#include "HitStruct.hpp"

class LambertShader : public Shader
{
public:
  LambertShader(const Vec3f& diffuse = renderer::constants::DEFAULT_DIFFUSE);
  virtual ~LambertShader() {}

  virtual Vec3f apply(const HitStruct& h) const;

protected:
  Vec3f m_diffuse;
};

#endif