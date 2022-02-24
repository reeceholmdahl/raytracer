#ifndef _SHADER_REECE_
#define _SHADER_REECE_

#include <string>

#include "Vector3.hpp"

class Shader
{
public:
  const static Vec3f DEFAULT_AMBIENT;

  Shader(const std::string &name, const Vec3f &ambient = DEFAULT_AMBIENT);
  virtual ~Shader() {}

  const std::string &name() const;
  const Vec3f &ambient() const;

protected:
  std::string m_name;
  Vec3f m_ambient;
};

#endif