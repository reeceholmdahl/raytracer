#ifndef RENDERER_SHADER_NORMAL_SHADER_H_
#define RENDERER_SHADER_NORMAL_SHADER_H_

#include "Shader.hpp"

class NormalShader : public Shader
{
public:
  NormalShader() = default;
  virtual ~NormalShader() {}

  virtual Vec3f apply(const HitStruct& hit) const;
};

#endif