#include "Box.hpp"
#include "Triangle.hpp"
#include "Vector3.hpp"

Box::Box() : Box(Vec3d(-0.25, -0.25, -2.25), Vec3d(0.25, 0.25, -1.75))
{
}

Box::Box(const Vec3d &min, const Vec3d &max) : m_min(min), m_max(max)
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
    double t(INFINITY);
    Triangle hitTri;
    int hitCount(0);
    for (Triangle tri : tris)
    {
        if (hitCount == 2)
            break;

        auto testHit = HitStruct(hit.tmin, hit.tmax);
        if (tri.closestHit(r, testHit))
        {
            ++hitCount;
            if (testHit.t < t)
            {
                t = testHit.t;
                hitTri = tri;
            }
        }
    }

    if (t != INFINITY)
    {
        hit.ray = r;
        hit.shaderPtr = getShader();
        hit.shape = this;
        hit.t = t;
        hit.normal = hitTri.normal(r.point(t));
        return true;
    }

    return false;
}