#ifndef RENDERER_GEOMETRY_BOX_H_
#define RENDERER_GEOMETRY_BOX_H_

#include <vector>

#include "Shape.hpp"
#include "Triangle.hpp"
#include "Vector3.hpp"
#include "BBox.hpp"

class Box : public Shape
{
public:
  Box();
  Box(const Vec3d& min, const Vec3d& max);
  virtual ~Box() {}

  virtual bool closestHit(const Ray& r, HitStruct& hit) const;
  virtual const BBox& bbox() const;
  virtual const Vec3d& centroid() const;

  inline virtual const std::string& type() const { return m_type; }

  inline virtual const std::string& name() const { return m_name; }

private:
  Vec3d m_min, m_max;
  std::vector<Triangle> tris;
  BBox m_bbox;
};

#endif