#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "BVH.hpp"
#include "HitStruct.hpp"
#include "BBox.hpp"

#define DEBUG_BVH 1

// TODO fix
// TODO research partitioning by surface area
BVHNode::BVHNode(std::vector<Shape*>& shapes,
                 std::vector<Shape*>::iterator first,
                 std::vector<Shape*>::iterator last)
  : Shape("bvh node")
  , left(nullptr)
  , right(nullptr)
{
  auto n = std::distance(first, last);
#if DEBUG_BVH
  std::cerr << "\n\n---BVH Node Creation---" << std::endl;

  if (n == 0) {
    std::cerr << "N == 0, this is an invalid case" << std::endl;
  } else
#endif

    if (n == 1) {
    left = *first;
#if DEBUG_BVH
    std::cerr << "This node has one child, a " << left->type() << std::endl;
#endif
    m_bbox = left->bbox();
  } else if (n == 2) {
    left = *first;
    right = *(first + 1);
#if DEBUG_BVH
    std::cerr << "This node has two children, a " << left->type() << " and a "
              << right->type() << std::endl;
#endif
    m_bbox = BBox::combine(left->bbox(), right->bbox());
  } else {
    // std::cout << "building bbox children" << std::endl;

    // find midpoint of bbox along
    double minx(INFINITY), maxx(-INFINITY), miny(INFINITY), maxy(-INFINITY),
      minz(INFINITY), maxz(-INFINITY);

    for (std::vector<Shape*>::iterator itr(first); itr < last; ++itr) {
      auto centroid = (*itr)->centroid();

      if (centroid[0] < minx)
        minx = centroid[0];

      if (centroid[1] < miny)
        miny = centroid[1];

      if (centroid[2] < minz)
        minz = centroid[2];

      if (centroid[0] > maxx)
        maxx = centroid[0];
      if (centroid[1] > maxy)
        maxy = centroid[1];
      if (centroid[2] > maxz)
        maxz = centroid[2];
    }

    double extent[3] = { std::abs(maxx - minx), std::abs(maxy - miny),
                         std::abs(maxz - minz) };

    int xyorz;
    double center;
    if (extent[0] > extent[1] && extent[0] > extent[2]) {
      // split along the x axis
      xyorz = 0;
      center = minx + (maxx - minx) / 2;
    } else {
      if (extent[1] > extent[2]) {
        // split along y axis
        xyorz = 1;
        center = miny + (maxy - miny) / 2;
      } else {
        // split along z axis
        xyorz = 2;
        center = minz + (maxz - minz) / 2;
      }
    }

#if DEBUG_BVH
    std::cerr << "Shapes assigned to this node: " << n << std::endl
              << "Partitioning along "
              << (xyorz == 0 ? 'X' : xyorz == 1 ? 'Y' : 'Z') << " axis"
              << std::endl
              << "Axis extent: " << extent[xyorz] << std::endl
              << "Center of axis: " << center << std::endl
              << "\nBefore partition" << std::endl;
#endif

    auto heuristic = [xyorz, center](Shape* shape) {
      return shape->centroid()[xyorz] < center;
    };

    auto split = std::partition(first, last, heuristic);

    if (split == first || split == first + (n - 1)) {
      split = first + 1;
#if DEBUG_BVH
      std::cerr << "Partition forced a manual split" << std::endl;
#endif
    }

#if DEBUG_BVH
    auto d1 = std::distance(first, split);
    auto d2 = std::distance(split, last);
    std::cerr << "After partition\n" << std::endl
              << "(Relatively) first at 0, split at " << d1 << ", last at "
              << d1 + d2 - 1 << std::endl
              << "(Memory addr) first: " << *first << std::endl
              << "split: " << *split << std::endl
              << "last: " << *last << std::endl;
#endif

    left = new BVHNode(shapes, first, split);
    right = new BVHNode(shapes, split, last);
    m_bbox = BBox::combine(left->bbox(), right->bbox());
  }
}

bool
BVHNode::closestHit(const Ray& r, HitStruct& hit) const
{

  // of Bboxes actually helps

  // std::cerr << "bbox min: " << m_bbox.minPt() << " max: " << m_bbox.maxPt()
  // << std::endl;

  double t;
  if (!m_bbox.hit(r, hit.tmin, hit.tmax, t))
    return false;

  HitStruct lhit(hit.tmin, hit.tmax, hit.lights), rhit(lhit);
  // std::cerr << "left ptr: " << left << std::endl;
  bool leftHit = left != nullptr && left->closestHit(r, lhit);
  // std::cerr << "right ptr: " << right << std::endl;
  bool rightHit = right != nullptr && right->closestHit(r, rhit);

  if (leftHit && rightHit) {
    if (lhit.t < rhit.t) {
      hit = lhit;
    } else {
      hit = rhit;
    }
  } else if (leftHit) {
    hit = lhit;
  } else if (rightHit) {
    hit = rhit;
  }

  return leftHit || rightHit;
}