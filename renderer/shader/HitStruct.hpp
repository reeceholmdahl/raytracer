#ifndef RENDERER_SHADER_HITSTRUCT_H_
#define RENDERER_SHADER_HITSTRUCT_H_

#include <vector>

#include "Vector3.hpp"
#include "Ray.hpp"

class Shader;
class Shape;
class Light;

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

  inline HitStruct(const double tmin = 1, const double tmax = INFINITY,
                   std::vector<Light*>* lights = nullptr)
    : tmin(tmin)
    , tmax(tmax)
    , lights(lights)
  {
  }

  inline HitStruct(const HitStruct& hit)
    : HitStruct(hit.tmin, hit.tmax, hit.lights)
  {
  }

  ~HitStruct() {}

  Vec3d hitPoint() const { return ray.point(t); }
};

#include "Shader.hpp"
#include "Shape.hpp"
#include "Light.hpp"

#endif