#ifndef RENDERER_SHADER_SHADER_H_
#define RENDERER_SHADER_SHADER_H_

#include "Constants.hpp"
#include "Vector3.hpp"

class HitStruct;

class Shader
{
public:
  Shader(const Vec3f& ambient = renderer::constants::DEFAULT_AMBIENT);
  virtual ~Shader() {}

  const Vec3f& ambient() const;

  virtual Vec3f apply(const HitStruct& h) const = 0;

protected:
  Vec3f m_ambient;
};

#endif