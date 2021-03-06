#ifndef _RENDERER_BBOX_H_
#define _RENDERER_BBOX_H_

#include "Vector3.hpp"
#include "Ray.hpp"

class BBox
{
public:
  static BBox combine(const BBox& b1, const BBox& b2);

  BBox();
  BBox(const Vec3d& min, const Vec3d& max);
  virtual ~BBox() {}

  bool hit(const Ray& r, const double tmin, const double tmax, double& t) const;

  inline const Vec3d& centroid() const { return m_centroid; }
  inline const Vec3d& minPt() const { return m_min; }
  inline const Vec3d& maxPt() const { return m_max; }

  inline double extentX() const { return m_max[0] - m_min[0]; }
  inline double extentY() const { return m_max[1] - m_min[1]; }
  inline double extentZ() const { return m_max[2] - m_min[2]; }

private:
  Vec3d m_min, m_max, m_centroid;
};

#endif