#ifndef _RENDERER_BBOX_H_
#define _RENDERER_BBOX_H_

#include "Vector3.hpp"
#include "Ray.hpp"

class BBox
{
public:
  BBox();
  BBox(const Vec3d& min, const Vec3d& max);
  virtual ~BBox() {}

  bool hit(const Ray& r, const double tmin, const double tmax, double& t) const;
  const Vec3d& centroid() const;
  const Vec3d& minPt() const;
  const Vec3d& maxPt() const;

  static BBox combine(const BBox& b1, const BBox& b2);

private:
  Vec3d m_min, m_max, m_centroid;
};

#endif