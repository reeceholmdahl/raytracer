#ifndef RENDERER_SHADER_NORMAL_SHADER_H_
#define RENDERER_SHADER_NORMAL_SHADER_H_

#include "Vector3.hpp"
#include "HitStruct.hpp"

class NormalShader : public Shader
{
public:
  NormalShader() = default;
  virtual ~NormalShader() {}

  virtual Vec3f apply(const HitStruct& h) const;
};

#endif