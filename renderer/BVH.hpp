#ifndef RENDERER_BVH_H_
#define RENDERER_BVH_H_

#include <vector>

#include "Shape.hpp"
#include "BBox.hpp"

class BVHNode : public Shape
{
public:
  Shape *left, *right;

  BVHNode() = delete;
  BVHNode(std::vector<Shape*>& shapes);
  BVHNode(std::vector<Shape*>& shapes, std::vector<Shape*>::iterator first,
          std::vector<Shape*>::iterator last);

  ~BVHNode()
  {
    if (left)
      delete left;
    if (right)
      delete right;
  }

  virtual bool closestHit(const Ray& r, HitStruct& hit) const;
  virtual const BBox& bbox() const;
  virtual const Vec3d& centroid() const;

private:
  BBox m_bbox;
};

class BVH
{
public:
  BVHNode* head;

  BVH() = delete;
  BVH(std::vector<Shape*>& shapes);

  ~BVH() { delete head; }
};

#endif