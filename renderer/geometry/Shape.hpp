#ifndef RENDERER_GEOMETRY_SHAPE_H_
#define RENDERER_GEOMETRY_SHAPE_H_

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "BBox.hpp"
#include "HitStruct.hpp"

class Shape
{
public:
  Shape() = delete;
  Shape(const std::string& type)
    : m_type(type)
  {
  }

  virtual ~Shape() {}

  virtual bool closestHit(const Ray& r, HitStruct& hit) const = 0;
  virtual const BBox& bbox() const = 0;
  virtual const Vec3d& centroid() const = 0;

  inline virtual const std::string& type() const { return m_type; }

  inline virtual const std::string& name() const { return m_name; }

  inline virtual void setName(const std::string& name) { m_name = name; }

  Shader* shaderPtr = nullptr;

protected:
  std::string m_type = "shape";
  std::string m_name = "unnamed";
};

#endif
