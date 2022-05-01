#include <cassert>

#include "Box.hpp"
#include "Triangle.hpp"
#include "Vector3.hpp"

// TODO move these to constants
Box::Box()
  : Box(Vec3d(-0.25, -0.25, -2.25), Vec3d(0.25, 0.25, -1.75))
{
}

Box::Box(const Vec3d& min, const Vec3d& max)
  : m_bbox(min, max)
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

    auto point = r.point(t);

    // TODO fix normal
    if (point[0] == m_min[0]) {
      hit.normal = Vec3d(-1, 0, 0);
    } else if (point[0] == m_max[0]) {
      hit.normal = Vec3d(1, 0, 0);
    } else if (point[1] == m_min[1]) {
      hit.normal = Vec3d(0, -1, 0);
    } else if (point[1] == m_max[1]) {
      hit.normal = Vec3d(0, 1, 0);
    } else if (point[2] == m_min[2]) {
      hit.normal = Vec3d(0, 0, -1);
    } else if (point[2] == m_max[2]) {
      hit.normal = Vec3d(0, 0, 1);
    } else {
      // std::cerr << "Could not give box a normal on hit. This should not
      // occur."
      //           << std::endl;
      assert(false);
    }

    return true;
  }

  return false;
}

const BBox&
Box::bbox() const
{
  return m_bbox;
}

const Vec3d&
Box::centroid() const
{
  return m_bbox.centroid();
}