#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "BVH.hpp"
#include "BBox.hpp"

constexpr auto h1 = [](int xyorz, double center, Shape* shape) {
  return shape->centroid()[xyorz] < center;
};

// TODO fix
// TODO research partitioning by surface area
BVHNode::BVHNode(std::vector<Shape*>& shapes,
                 const std::vector<Shape*>::iterator& begin,
                 const std::vector<Shape*>::iterator& end)
  : Shape("bvh node")
  , left(nullptr)
  , right(nullptr)
{
  setName("bvh bbox");
  auto n = std::distance(begin, end);
#if DEBUG_BVH_CREATE
  std::cerr << "\n\n---BVH Node Creation---" << std::endl;

  if (n == 0) {
    std::cerr << "N == 0, this is an invalid case" << std::endl;
  } else
#endif

    if (n == 1) {
    left = *begin;
#if DEBUG_BVH_CREATE
    std::cerr << "This node has one child, a " << left->type() << std::endl;
#endif
    m_bbox = left->bbox();
  } else if (n == 2) {
    left = *begin;
    right = *(begin + 1);
#if DEBUG_BVH_CREATE
    std::cerr << "This node has two children, a " << left->type() << " and a "
              << right->type() << std::endl;
#endif
    m_bbox = BBox::combine(left->bbox(), right->bbox());
  } else {
    // std::cout << "building bbox children" << std::endl;

    // find midpoint of bbox along
    double minx(INFINITY), maxx(-INFINITY), miny(INFINITY), maxy(-INFINITY),
      minz(INFINITY), maxz(-INFINITY);

    Vec3d weightedExtent;
    Vec3d average;

    for (std::vector<Shape*>::iterator itr(begin); itr < end; ++itr) {
      auto shape(*itr);
      auto centroid(shape->centroid());

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

      weightedExtent += Vec3d(std::abs(centroid[0]), std::abs(centroid[1]),
                              std::abs(centroid[2]));
      average += centroid;
    }

    double extent[3] = { std::abs(maxx - minx), std::abs(maxy - miny),
                         std::abs(maxz - minz) };

    average /= n;
    weightedExtent /= n;

    int xyorz;
    double center;
    if (weightedExtent[0] > weightedExtent[1] &&
        weightedExtent[0] > weightedExtent[2]) {
      xyorz = 0;
    } else if (weightedExtent[1] > weightedExtent[2]) {
      xyorz = 1;
    } else {
      xyorz = 2;
    }
    center = average[xyorz];
// if (extent[0] > extent[1] && extent[0] > extent[2]) {
//   // split along the x axis
//   xyorz = 0;
//   center = minx + (maxx - minx) / 2;
// } else {
//   if (extent[1] > extent[2]) {
//     // split along y axis
//     xyorz = 1;
//     center = miny + (maxy - miny) / 2;
//   } else {
//     // split along z axis
//     xyorz = 2;
//     center = minz + (maxz - minz) / 2;
//   }
// }

#if DEBUG_BVH_CREATE
    std::cerr << "Shapes assigned to this node: " << n << std::endl
              << "Partitioning along "
              << (xyorz == 0 ? 'X' : xyorz == 1 ? 'Y' : 'Z') << " axis"
              << std::endl
              << "Axis weighted extent: " << weightedExtent[xyorz] << std::endl
              << "Center of axis: " << center << std::endl
              << "\nBefore partition" << std::endl;
#endif

    auto heuristic = [xyorz, center](Shape* shape) {
      return h1(xyorz, center, shape);
    };

    auto split = std::partition(begin, end, heuristic);

    if (split == begin || split == begin + (n - 1)) {
#if DEBUG_BVH_CREATE
      std::cerr << "Partition forced a manual split, d1: "
                << std::distance(begin, split) << ", d2 is "
                << std::distance(split, end) << std::endl;
#endif
      split = begin + 1;
    }

    auto d1 = std::distance(begin, split);
    auto d2 = std::distance(split, end);

#if DEBUG_BVH_CREATE
    std::cerr << "After partition\n" << std::endl
              << "(Relatively) begin at 0, split at " << d1 << ", end at "
              << d1 + d2 << std::endl
              << "(Memory addr) begin: " << *begin << ", split: " << *split
              << ", end: " << *end << ", d1: " << *(begin + d1) << std::endl;
#endif

    // evens out tree more?
    if ((d1 + d2) % 2 == 0 && d1 % 2 == 1) {
      if (d1 < d2) {
        ++d1;
        --d2;
        ++split;
      } else {
        split = begin + (d1 - 1);
        --d1;
        ++d2;
      }
#if DEBUG_BVH_CREATE
      std::cerr << "Modifying partition split to make trees even" << std::endl
                << "Left split N == " << d1 << " Right split N == " << d2
                << std::endl;
#endif
    }

    left = new BVHNode(shapes, begin, split);
    right = new BVHNode(shapes, split, end);
    m_bbox = BBox::combine(left->bbox(), right->bbox());
  }
}

bool
BVHNode::closestHit(const Ray& r, HitStruct& hit) const
{
  double t;
  if (!m_bbox.hit(r, hit.tmin, hit.tmax, t))
    return false;

  HitStruct lhit(t, hit.tmax, hit.scene), rhit(lhit);
#if DEBUG_BVH_HIT
  std::cerr << "lhit: tmin: " << lhit.tmin << " tmax: " << lhit.tmax
            << " num lights: " << lhit.lights->size() << std::endl
            << "lhit: tmin: " << rhit.tmin << " tmax: " << rhit.tmax
            << " num lights: " << rhit.lights->size() << std::endl;
#endif
  bool leftHit = left && left->closestHit(r, lhit);
  // std::cerr << "right ptr: " << right << std::endl;
  bool rightHit = right && right->closestHit(r, rhit);

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

// TODO does this need to actually parameter return &hit?
bool
BVHNode::anyHit(const Ray& r, HitStruct& hit) const
{
  double t;
  if (!m_bbox.hit(r, hit.tmin, hit.tmax, t))
    return false;

  HitStruct lhit(t, hit.tmax, hit.scene), rhit(lhit);
#if DEBUG_BVH_HIT
  std::cerr << "lhit: tmin: " << lhit.tmin << " tmax: " << lhit.tmax
            << " num lights: " << lhit.lights->size() << std::endl
            << "lhit: tmin: " << rhit.tmin << " tmax: " << rhit.tmax
            << " num lights: " << rhit.lights->size() << std::endl;
#endif

  if (left) {
    bool leftHit(false);
    if (left->type() == "bvh node") {
      auto node = dynamic_cast<BVHNode*>(left);
      leftHit = node->anyHit(r, lhit);
    } else {
      leftHit = left->closestHit(r, lhit);
    }

    if (leftHit) {
      hit = lhit;
      return true;
    }
  }

  if (right) {
    bool rightHit(false);
    if (right->type() == "bvh node") {
      auto node = dynamic_cast<BVHNode*>(right);
      rightHit = node->anyHit(r, rhit);
    } else {
      rightHit = right->closestHit(r, rhit);
    }

    if (rightHit) {
      hit = rhit;
      return true;
    }
  }

  return false;
}