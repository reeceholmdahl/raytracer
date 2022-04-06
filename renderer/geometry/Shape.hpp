#ifndef RENDERER_GEOMETRY_SHAPE_H_
#define RENDERER_GEOMETRY_SHAPE_H_

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Shader.hpp"

class Shape
{
public:
  Shape(Shader *shaderPtr = nullptr);
  virtual ~Shape() {}

  virtual bool closestHit(const Ray &r, const double tmin, const double tmax, HitStruct &hit) const = 0;

  virtual Vec3d normal(const Vec3d &position) const = 0;

  void setShader(Shader *shaderPtr);
  Shader *getShader() const;

protected:
  Shader *m_shaderPtr;
};

#endif
#include "HitStruct.hpp"