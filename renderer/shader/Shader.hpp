#ifndef _SHADER_REECE_
#define _SHADER_REECE_

#include "Vector3.hpp"

class HitStruct;

class Shader
{
public:
  const static Vec3f DEFAULT_AMBIENT;
  static Shader *NULL_SHADER;

  Shader(const Vec3f &ambient = DEFAULT_AMBIENT);
  virtual ~Shader() {}

  const Vec3f &ambient() const;

  virtual Vec3f apply(const HitStruct &h) const = 0;

protected:
  Vec3f m_ambient;
};

#endif