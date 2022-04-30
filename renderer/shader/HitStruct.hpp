#ifndef RENDERER_SHADER_HITSTRUCT_H_
#define RENDERER_SHADER_HITSTRUCT_H_

#include <vector>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "Light.hpp"

class HitStruct
{
public:
  double t = INFINITY;
  double tmin;
  double tmax;

  // could be a reference
  Ray ray;
  Vec3d normal;
  Shader* shaderPtr;
  const Shape* shape;

  // TODO this could be made more efficient
  std::vector<Light*>* lights;

  HitStruct(const double tmin = 1, const double tmax = INFINITY,
            std::vector<Light*>* lights = nullptr)
    : tmin(tmin)
    , tmax(tmax)
    , lights(lights)
  {
  }

  ~HitStruct() {}

  Vec3d hitPoint() const { return ray.point(t); }
};

#endif