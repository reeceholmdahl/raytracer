#ifndef _SHADER_REECE_
#define _SHADER_REECE_

#include <string>

class Shader
{
public:
  Shader() = default;
  virtual ~Shader() {}

  virtual std::string name() const = 0;
};

#endif