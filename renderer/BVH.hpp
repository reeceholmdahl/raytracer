#ifndef RENDERER_BVH_H_
#define RENDERER_BVH_H_

#include <iostream>
#include <vector>

#include "Shape.hpp"
#include "BBox.hpp"
#include "Constants.h"

#define DEBUG_BVH_CREATE 1
#define DEBUG_BVH_HIT 0

class BVHNode : public Shape
{
public:
  Shape *left, *right;

  BVHNode() = delete;
  BVHNode::BVHNode(std::vector<Shape*>& shapes)
    : BVHNode(shapes, shapes.begin(), shapes.end())
  {
  }
  BVHNode(std::vector<Shape*>& shapes,
          const std::vector<Shape*>::iterator& begin,
          const std::vector<Shape*>::iterator& end);

  ~BVHNode()
  {
    if (left)
      delete left;
    if (right)
      delete right;
  }

  virtual bool closestHit(const Ray& r, HitStruct& hit) const;
  bool anyHit(const Ray& r, HitStruct& hit) const;

  virtual const BBox& bbox() const { return m_bbox; }
  virtual const Vec3d& centroid() const { return m_bbox.centroid(); }
  virtual const std::string& type() const { return m_type; }
  virtual const std::string& name() const { return m_name; }

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

  BVH::BVH(std::vector<Shape*>& shapes)
    : head(new BVHNode(shapes))
  {
#if DEBUG_BVH_CREATE
    print();
#endif
  }

  ~BVH() { delete head; }

  void print(const std::ostream& os = std::cout) const
  {
    print("", head, false, os);
  }

private:
  void print(const std::string& prefix, Shape* node, bool isLeft,
             const std::ostream& os) const;
};

#endif