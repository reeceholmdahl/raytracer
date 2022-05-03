#ifndef RENDERER_GEOMETRY_TRIANGLE_H_
#define RENDERER_GEOMETRY_TRIANGLE_H_

#include "Shape.hpp"

class Triangle : public Shape
{
public:
  Triangle();
  Triangle(const Vec3d& a, const Vec3d& b, const Vec3d& c);
  virtual ~Triangle() {}

  virtual bool closestHit(const Ray& r, HitStruct& hit) const;

  inline virtual const BBox& bbox() const { return m_bbox; }
  inline virtual const Vec3d& centroid() const { return m_bbox.centroid(); }
  inline virtual const std::string& type() const { return m_type; }
  inline virtual const std::string& name() const { return m_name; }

  const Vec3d& normal() const;

private:
  Vec3d m_a, m_b, m_c, m_normal;
  BBox m_bbox;

  friend void calcBarycentricCoords(const Triangle& tri,
                                    const Vec3d& p,
                                    double& alpha,
                                    double& beta,
                                    double& gamma);
};

#endif