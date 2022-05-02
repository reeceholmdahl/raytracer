#ifndef RENDERER_BVH_H_
#define RENDERER_BVH_H_

#include <iostream>
#include <vector>

#include "Shape.hpp"
#include "BBox.hpp"
#include "Constants.h"

class BVHNode : public Shape
{
public:
  Shape *left, *right;

  BVHNode() = delete;
  inline BVHNode::BVHNode(std::vector<Shape*>& shapes)
    : BVHNode(shapes, shapes.begin(), shapes.end())
  {
  }
  BVHNode(std::vector<Shape*>& shapes, std::vector<Shape*>::iterator first,
          std::vector<Shape*>::iterator last);

  inline ~BVHNode()
  {
    if (left)
      delete left;
    if (right)
      delete right;
  }

  virtual bool closestHit(const Ray& r, HitStruct& hit) const;
  bool anyHit(const Ray& r, HitStruct& hit) const;

  inline virtual const BBox& bbox() const { return m_bbox; }
  inline virtual const Vec3d& centroid() const { return m_bbox.centroid(); }
  inline virtual const std::string& type() const { return m_type; }
  inline virtual const std::string& name() const { return m_name; }

private:
  BBox m_bbox;
};

class BVH
{
public:
  BVHNode* const head;

  inline BVH()
    : head(nullptr)
  {
  }

  inline BVH::BVH(std::vector<Shape*>& shapes, bool debugPrint = false)
    : head(new BVHNode(shapes))
  {
    if (debugPrint)
      print();
  }

  inline ~BVH() { delete head; }

  inline void print(const std::ostream& os = std::cout) const
  {
    print("", head, false, os);
  }

private:
  void print(const std::string& prefix, Shape* node, bool isLeft,
             const std::ostream& os) const;
};

#endif