#ifndef RENDERER_GEOMETRY_SPHERE_H_
#define RENDERER_GEOMETRY_SPHERE_H_

#include "Shape.hpp"
#include "HitStruct.hpp"
#include "Vector3.hpp"

class Sphere : public Shape
{
public:
  Sphere();
  Sphere(const Vec3d& position, const double radius);
  virtual ~Sphere() {}

  virtual bool closestHit(const Ray& r, HitStruct& hit) const;
  virtual const BBox& bbox() const;
  virtual const Vec3d& centroid() const;

  Vec3d normal(const Vec3d& position) const;

private:
  Vec3d m_position;
  double m_radius;
  BBox m_bbox;
};

#endif