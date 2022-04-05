#ifndef RENDERER_GEOMETRY_SHAPE_H_
#define RENDERER_GEOMETRY_SHAPE_H_

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Shader.hpp"

class Shape
{
public:
  Shape(Shader *shaderPtr = Shader::NULL_SHADER);
  virtual ~Shape() {}

  virtual bool closestHit(const Ray &r, const double tmin, const double tmax, HitStruct &hit) const = 0;

  virtual Vec3d normal(const Vec3d &position) const = 0;

  //! protected: set to protected later with friend accessor for scene container/json parser
  Shader *shaderPtr;
};

#endif
#include "HitStruct.hpp"