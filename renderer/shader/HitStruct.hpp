#ifndef _HITSTRUCT_REECE_
#define _HITSTRUCT_REECE_

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "Shape.hpp"

class HitStruct
{
public:
    double t;
    Ray ray;
    Shader *shaderPtr;
    const Shape *shape;

    HitStruct() = default;
    ~HitStruct() {}

    Vec3d hitPoint()
    {
        return ray.point(t);
    }
};

#endif