#ifndef RENDERER_SHADER_HITSTRUCT_H_
#define RENDERER_SHADER_HITSTRUCT_H_

#include <vector>

#include "Vector3.hpp"
#include "Ray.hpp"

class Shader;
class Shape;
class Scene;

class HitStruct
{
public:
  double t;
  double tmin;
  double tmax;

  Ray ray;
  Vec3d normal;
  Shader* shaderPtr;
  const Shape* shape;
  const Scene* scene;

  inline HitStruct(const double tmin = 1, const double tmax = INFINITY,
                   const Scene* scene = nullptr)
    : t(INFINITY)
    , tmin(tmin)
    , tmax(tmax)
    , scene(scene)
  {
  }

  inline HitStruct(const HitStruct& hit)
    : t(hit.t)
    , tmin(hit.tmin)
    , tmax(hit.tmax)
    , ray(hit.ray)
    , normal(hit.normal)
    , shaderPtr(hit.shaderPtr)
    , shape(hit.shape)
    , scene(hit.scene)
  {
  }

  ~HitStruct() {}

  inline Vec3d hitPoint() const { return ray.point(t); }
};

#endif