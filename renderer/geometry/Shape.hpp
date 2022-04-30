#ifndef RENDERER_GEOMETRY_SHAPE_H_
#define RENDERER_GEOMETRY_SHAPE_H_

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "BBox.hpp"

class Shape
{
public:
  // TODO move default shader to constants
  Shape() {}
  virtual ~Shape() {}

  virtual bool closestHit(const Ray& r, HitStruct& hit) const = 0;
  virtual const BBox& bbox() const = 0;
  virtual const Vec3d& centroid() const = 0;

  Shader* shaderPtr = nullptr;
  std::string name = "Unnamed";
};

#endif
#include "HitStruct.hpp"