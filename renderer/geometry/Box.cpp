#include <cassert>

#include "Box.hpp"

// TODO move these to constants
Box::Box()
  : Box(Vec3d(-0.25, -0.25, -2.25), Vec3d(0.25, 0.25, -1.75))
{
}

Box::Box(const Vec3d& min, const Vec3d& max)
  : Shape("box")
  , m_bbox(min, max)
{
}

bool
Box::closestHit(const Ray& r, HitStruct& hit) const
{
  double t;
  if (m_bbox.hit(r, hit.tmin, hit.tmax, t)) {
    hit.ray = r;
    hit.shaderPtr = shaderPtr;
    hit.shape = this;
    hit.t = t;

    auto dcenter = r.point(t) - centroid();

    auto dx = std::abs(dcenter[0]) / m_bbox.extentX();
    auto dy = std::abs(dcenter[1]) / m_bbox.extentY();
    auto dz = std::abs(dcenter[2]) / m_bbox.extentZ();

    if (dx > dy && dx > dz) {
      hit.normal = Vec3d(dcenter[0] > 0 ? 1 : -1, 0, 0);
    } else if (dy > dz) {
      hit.normal = Vec3d(0, dcenter[1] > 0 ? 1 : -1, 0);
    } else {
      hit.normal = Vec3d(0, 0, dcenter[2] > 0 ? 1 : -1);
    }

    // hit.normal = Vec3d(0, 1, 0);

    return true;
  }

  return false;
}