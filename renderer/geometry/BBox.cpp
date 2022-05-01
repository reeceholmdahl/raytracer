#include "BBox.hpp"

#include <algorithm>

#define DEBUG_BBOX 0

BBox::BBox()
  : BBox(Vec3d(-0.25, -0.25, -2.25), Vec3d(0.25, 0.25, -1.75))
{
}

BBox::BBox(const Vec3d& min, const Vec3d& max)
  : m_min(min)
  , m_max(max)
{
  m_centroid = (m_min + m_max) / 2;
}

bool
BBox::hit(const Ray& r, double tmin, double tmax, double& t) const
{
  // TODO could there be a way to choose the axis that it checks overlap first
  // based on the scene's extent?

  auto rtomin(m_min - r.origin());
  auto rtomax(m_max - r.origin());

  auto dir(r.direction());

  auto tminx = rtomin[0] / dir[0];
  auto tmaxx = rtomax[0] / dir[0];

  if (1 / dir[0] < 0)
    std::swap(tminx, tmaxx);

  // Ray overlaps box on x
  if (tminx < tmaxx && tminx < tmax && tmaxx > tmin) {
    tmax = tmaxx;
    tmin = std::max(tmin, tminx);

    auto tminy = rtomin[1] / dir[1];
    auto tmaxy = rtomax[1] / dir[1];

    if (1 / dir[1] < 0)
      std::swap(tminy, tmaxy);

    // Ray overlaps box on x AND y
    if (tminy < tmaxy && tminy < tmax && tmaxy > tmin) {
      tmax = std::min(tmax, tmaxy);
      tmin = std::max(tmin, tminy);

      auto tminz = rtomin[2] / dir[2];
      auto tmaxz = rtomax[2] / dir[2];

      if (1 / dir[2] < 0)
        std::swap(tminz, tmaxz);

      // If Ray overlaps box on x and y AND z then box is hit, otherwise is not.
      if (tminz < tmaxz && tminz < tmax && tmaxz > tmin) {
        t = std::max(tminz, tmin);
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}

BBox
BBox::combine(const BBox& b1, const BBox& b2)
{
  Vec3d min(std::min(b1.m_min[0], b2.m_min[0]),
            std::min(b1.m_min[1], b2.m_min[1]),
            std::min(b1.m_min[2], b2.m_min[2]));

  Vec3d max(std::max(b1.m_max[0], b2.m_max[0]),
            std::max(b1.m_max[1], b2.m_max[1]),
            std::max(b1.m_max[2], b2.m_max[2]));

  return BBox(min, max);
}

const Vec3d&
BBox::centroid() const
{
  return m_centroid;
}
const Vec3d&
BBox::minPt() const
{
  return m_min;
}
const Vec3d&
BBox::maxPt() const
{
  return m_max;
}