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

  int depth;

  Ray ray;
  Vec3d normal;
  Shader* shaderPtr;
  const Shape* shape;
  const Scene* scene;

  HitStruct(const double tmin = 1, const double tmax = INFINITY,
            const Scene* scene = nullptr, const int depth = 0)
    : tmin(tmin)
    , tmax(tmax)
    , t(tmax)
    , scene(scene)
    , depth(depth)
    , shaderPtr(nullptr)
    , shape(nullptr)
  {
  }

  HitStruct(const HitStruct& hit)
    : t(hit.t)
    , tmin(hit.tmin)
    , tmax(hit.tmax)
    , ray(hit.ray)
    , normal(hit.normal)
    , shaderPtr(hit.shaderPtr)
    , shape(hit.shape)
    , scene(hit.scene)
    , depth(hit.depth)
  {
  }

  ~HitStruct() {}

  Vec3d hitPoint() const { return ray.point(t); }
};

#endif