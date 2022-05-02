#ifndef RENDERER_SHADER_LAMBERT_SHADER_H_
#define RENDERER_SHADER_LAMBERT_SHADER_H_

#include "Shader.hpp"

class LambertShader : public Shader
{
public:
  LambertShader(const Vec3f& diffuse = renderer::constants::DEFAULT_DIFFUSE);
  virtual ~LambertShader() {}

  virtual Vec3f apply(const HitStruct& hit) const;

protected:
  Vec3f m_diffuse;
};

#endif