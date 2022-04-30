#ifndef RENDERER_GEOMETRY_TRIANGLE_H_
#define RENDERER_GEOMETRY_TRIANGLE_H_

#include "Vector3.hpp"
#include "Shape.hpp"

class Triangle : public Shape
{
public:
  Triangle();
  Triangle(const Vec3d &a, const Vec3d &b, const Vec3d &c);
  virtual ~Triangle() {}

  virtual bool closestHit(const Ray &r, HitStruct &hit) const;
  virtual const BBox &bbox() const;
  virtual const Vec3d &centroid() const;

  const Vec3d &normal(const Vec3d &position) const;

private:
  Vec3d m_a, m_b, m_c, m_normal;
  BBox m_bbox;
};

#endif