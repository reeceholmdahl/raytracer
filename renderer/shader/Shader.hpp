#ifndef RENDERER_SHADER_SHADER_H_
#define RENDERER_SHADER_SHADER_H_

#include "Constants.h"
#include "Vector3.hpp"
#include "HitStruct.hpp"

class Shader
{
public:
  inline Shader(const Vec3f& ambient = renderer::constants::DEFAULT_AMBIENT)
    : m_ambient(ambient)
  {
  }
  virtual ~Shader() {}

  const Vec3f& ambient() const { return m_ambient; }

  virtual Vec3f apply(const HitStruct& hit) const = 0;

protected:
  Vec3f m_ambient;
};

#endif