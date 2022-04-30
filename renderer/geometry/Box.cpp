#include "Box.hpp"
#include "Triangle.hpp"
#include "Vector3.hpp"

Box::Box() : Box(Vec3d(-0.25, -0.25, -2.25), Vec3d(0.25, 0.25, -1.75))
{
}

Box::Box(const Vec3d &min, const Vec3d &max) : m_min(min), m_max(max), m_bbox(min, max)
{
    // Initialize triangles for box
    tris = {
        Triangle(Vec3d(min[0], min[1], min[2]), Vec3d(max[0], max[1], min[2]), Vec3d(max[0], min[1], min[2])),
        Triangle(Vec3d(min[0], min[1], min[2]), Vec3d(min[0], max[1], min[2]), Vec3d(max[0], max[1], min[2])),
        Triangle(Vec3d(min[0], min[1], max[2]), Vec3d(min[0], max[1], min[2]), Vec3d(min[0], min[1], min[2])),
        Triangle(Vec3d(min[0], min[1], max[2]), Vec3d(min[0], max[1], max[2]), Vec3d(min[0], max[1], min[2])),
        Triangle(Vec3d(max[0], min[1], max[2]), Vec3d(min[0], max[1], max[2]), Vec3d(min[0], min[1], max[2])),
        Triangle(Vec3d(max[0], min[1], max[2]), Vec3d(max[0], max[1], max[2]), Vec3d(min[0], max[1], max[2])),
        Triangle(Vec3d(max[0], min[1], min[2]), Vec3d(max[0], max[1], max[2]), Vec3d(max[0], min[1], max[2])),
        Triangle(Vec3d(max[0], min[1], min[2]), Vec3d(max[0], max[1], min[2]), Vec3d(max[0], max[1], max[2])),
        Triangle(Vec3d(max[0], max[1], max[2]), Vec3d(min[0], max[1], min[2]), Vec3d(min[0], max[1], max[2])),
        Triangle(Vec3d(max[0], max[1], max[2]), Vec3d(max[0], max[1], min[2]), Vec3d(min[0], max[1], min[2])),
        Triangle(Vec3d(max[0], min[1], min[2]), Vec3d(min[0], min[1], max[2]), Vec3d(min[0], min[1], min[2])),
        Triangle(Vec3d(max[0], min[1], min[2]), Vec3d(max[0], min[1], max[2]), Vec3d(min[0], min[1], max[2])),
    };
}

bool Box::closestHit(const Ray &r, HitStruct &hit) const
{
    // double t(INFINITY);
    // Triangle hitTri;
    // int hitCount(0);
    // for (Triangle tri : tris)
    // {
    //     if (hitCount == 2)
    //         break;

    //     auto testHit = HitStruct(hit.tmin, hit.tmax);
    //     if (tri.closestHit(r, testHit))
    //     {
    //         ++hitCount;
    //         if (testHit.t < t)
    //         {
    //             t = testHit.t;
    //             hitTri = tri;
    //         }
    //     }
    // }

    // if (t != INFINITY)
    // {
    //     hit.ray = r;
    //     hit.shaderPtr = getShader();
    //     hit.shape = this;
    //     hit.t = t;

    //     return true;
    // }

    // return false;

    double t;
    if (m_bbox.hit(r, hit.tmin, hit.tmax, t))
    {
        hit.ray = r;
        hit.shaderPtr = getShader();
        hit.shape = this;
        hit.t = t;

        // TODO fix normal
        if (r.point(t)[0] == m_min[0])
        {
            hit.normal = Vec3d(-1, 0, 0);
        }
        else if (r.point(t)[0] == m_max[0])
        {
            hit.normal = Vec3d(1, 0, 0);
        }
        else if (r.point(t)[1] == m_min[1])
        {
            hit.normal = Vec3d(0, -1, 0);
        }
        else if (r.point(t)[1] == m_max[1])
        {
            hit.normal = Vec3d(0, 1, 0);
        }
        else if (r.point(t)[2] == m_min[2])
        {
            hit.normal = Vec3d(0, 0, -1);
        }
        else if (r.point(t)[2] == m_max[2])
        {
            hit.normal = Vec3d(0, 0, 1);
        }

        return true;
    }

    return false;
}

const BBox &Box::bbox() const
{
    return m_bbox;
}

const Vec3d &Box::centroid() const
{
    return m_bbox.centroid();
}