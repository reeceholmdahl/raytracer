#include "BBox.hpp"

#include <algorithm>

#define DEBUG_BBOX 0

BBox::BBox() : BBox(Vec3d(-0.25, -0.25, -2.25), Vec3d(0.25, 0.25, -1.75))
{
}

BBox::BBox(const Vec3d &min, const Vec3d &max) : m_min(min), m_max(max)
{
    m_centroid = (m_min + m_max) / 2;
}

bool BBox::hit(const Ray &r, const double tmin, const double tmax, double &t) const
{

    auto rtomin(m_min - r.origin());
    auto rtomax(m_max - r.origin());

    auto tminx = rtomin[0] / r.direction()[0];
    auto tminy = rtomin[1] / r.direction()[1];
    auto tminz = rtomin[2] / r.direction()[2];

    auto tmaxx = rtomax[0] / r.direction()[0];
    auto tmaxy = rtomax[1] / r.direction()[1];
    auto tmaxz = rtomax[2] / r.direction()[2];

#if DEBUG_BBOX
    std::cerr << "\nBBox hit calculations"
              << std::endl;
    std::cerr << "Before swap" << std::endl
              << "tminx: " << tminx << std::endl
              << "tmaxx: " << tmaxx << std::endl
              << "tminy: " << tminy << std::endl
              << "tmaxy: " << tmaxy << std::endl
              << "tminz: " << tminz << std::endl
              << "tmaxz: " << tmaxz << std::endl;
#endif

    if (1 / r.direction()[0] < 0)
    {
        std::swap(tminx, tmaxx);
    }

    if (1 / r.direction()[1] < 0)
    {
        std::swap(tminy, tmaxy);
    }

    if (1 / r.direction()[2] < 0)
    {
        std::swap(tminz, tmaxz);
    }

#if DEBUG_BBOX
    std::cerr << "After swap" << std::endl
              << "tminx: " << tminx << std::endl
              << "tmaxx: " << tmaxx << std::endl
              << "tminy: " << tminy << std::endl
              << "tmaxy: " << tmaxy << std::endl
              << "tminz: " << tminz << std::endl
              << "tmaxz: " << tmaxz << std::endl;
#endif

    auto intersectMin = std::max({tminx, tminy, tminz});
    auto intersectMax = std::min({tmaxx, tmaxy, tmaxz});

#if DEBUG_BBOX
    std::cerr << "intersectMin: " << intersectMin << std::endl
              << "intersectMax: " << intersectMax << std::endl;
#endif

    t = std::min(tmin, intersectMin);

    // return intersectMin <= intersectMax && (intersectMin <= tmax || intersectMax >= tmin);
    return intersectMin <= intersectMax;
}

BBox BBox::combine(const BBox &b1, const BBox &b2)
{
    Vec3d min(std::min(b1.m_min[0], b2.m_min[0]),
              std::min(b1.m_min[1], b2.m_min[1]),
              std::min(b1.m_min[2], b2.m_min[2]));

    Vec3d max(std::max(b1.m_max[0], b2.m_max[0]),
              std::max(b1.m_max[1], b2.m_max[1]),
              std::max(b1.m_max[2], b2.m_max[2]));

    return BBox(min, max);
}

const Vec3d &BBox::centroid() const
{
    return m_centroid;
}
const Vec3d &BBox::minPt() const
{
    return m_min;
}
const Vec3d &BBox::maxPt() const
{
    return m_max;
}