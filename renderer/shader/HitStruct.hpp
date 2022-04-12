#ifndef RENDERER_SHADER_HITSTRUCT_H_
#define RENDERER_SHADER_HITSTRUCT_H_

#include <vector>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "Light.hpp"

class HitStruct
{
public:
    double t;
    Ray ray;
    Shader *shaderPtr;
    const Shape *shape;
    std::vector<Light *> m_lights;

    HitStruct(const std::vector<Light *> &lights = {})
    {
        m_lights = lights;
    }
    ~HitStruct() {}

    Vec3d hitPoint() const
    {
        return ray.point(t);
    }
};

#endif