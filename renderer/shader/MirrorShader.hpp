#ifndef RENDERER_SHADER_MIRROR_SHADER_H_
#define RENDERER_SHADER_MIRROR_SHADER_H_

#include "Shader.hpp"

class MirrorShader : public Shader
{
public:
  MirrorShader() = default;
  virtual ~MirrorShader() {}

  virtual Vec3f apply(const HitStruct& hit) const;
};

#endif