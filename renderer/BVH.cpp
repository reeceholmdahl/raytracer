#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "BVH.hpp"
#include "HitStruct.hpp"
#include "BBox.hpp"

BVHNode::BVHNode(std::vector<Shape *> &shapes) : BVHNode(shapes, shapes.begin(), shapes.end()) {}

BVHNode::BVHNode(std::vector<Shape *> &shapes, std::vector<Shape *>::iterator first, std::vector<Shape *>::iterator last) : left(nullptr), right(nullptr)
{
    // std::cerr << "first: " << *first << std::endl;
    // std::cerr << "last: " << *last << std::endl;

    auto n = std::distance(first, last);
    // std::cerr << "n is: " << n << std::endl;
    if (n == 0)
    {
        // shouldn't ever be here
        assert(false);
    }
    else if (n == 1)
    {
        left = *first;
        // std::cerr << "left: " << left << std::endl;
        m_bbox = left->bbox();
    }
    else if (n == 2)
    {
        left = *first;
        right = *(first + 1);
        // std::cerr << "left: " << left << std::endl;
        // std::cerr << "right: " << right << std::endl;
        m_bbox = BBox::combine(left->bbox(), right->bbox());
    }
    else
    {
        // std::cout << "building bbox children" << std::endl;

        // find midpoint of bbox along
        double minx(INFINITY),
            maxx(-INFINITY), miny(INFINITY), maxy(-INFINITY), minz(INFINITY), maxz(-INFINITY);

        for (auto shape : shapes)
        {
            // std::cerr << "Before centroid" << std::endl;
            auto centroid = shape->centroid();
            // std::cerr << "After centroid" << std::endl;

            // std::cerr << centroid << std::endl;

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

        double extentx = std::abs(maxx - minx);
        double extenty = std::abs(maxy - miny);
        double extentz = std::abs(maxz - minz);

        int xyorz;
        double center;
        if (extentx > extenty && extentx > extentz)
        {
            // split along the x axis
            xyorz = 0;
            center = (maxx + minx) / 2;
        }
        else
        {
            if (extenty > extentz)
            {
                // split along y axis
                xyorz = 1;
                center = (maxy + miny) / 2;
            }
            else
            {
                // split along z axis
                xyorz = 2;
                center = (maxz + minz) / 2;
            }
        }

        // TODO partition by SA?
        // std::cerr << "Before partition\n";

        auto split = std::partition(first, last,
                                    [xyorz, center](Shape *shape)
                                    { return shape->centroid()[xyorz] < center; });

        // std::cerr << "After partition" << std::endl;

        if (split == first || split == last)
        {
            split = first + 1;
            // std::cerr << "Manual split" << std::endl;
        }

        // std::cerr << "first: " << *first << std::endl;
        // std::cerr << "last: " << *last << std::endl;
        // std::cerr << "split: " << *split << std::endl;

        left = new BVHNode(shapes, first, split);
        right = new BVHNode(shapes, split + 1, last);
        m_bbox = BBox::combine(left->bbox(), right->bbox());
    }
}

bool BVHNode::closestHit(const Ray &r, HitStruct &hit) const
{
    // std::cerr << "bbox min: " << m_bbox.minPt() << " max: " << m_bbox.maxPt() << std::endl;

    double t;
    if (!m_bbox.hit(r, hit.tmin, hit.tmax, t))
        return false;

    HitStruct lhit(hit.tmin, hit.tmax, hit.lights), rhit(hit.tmin, hit.tmax, hit.lights);
    // std::cerr << "left ptr: " << left << std::endl;
    bool leftHit = left != nullptr && left->closestHit(r, lhit);
    // std::cerr << "right ptr: " << right << std::endl;
    bool rightHit = right != nullptr && right->closestHit(r, rhit);

    if (leftHit && rightHit)
    {
        if (lhit.t < rhit.t)
        {
            hit = lhit;
        }
        else
        {
            hit = rhit;
        }
    }
    else if (leftHit)
    {
        hit = lhit;
    }
    else if (rightHit)
    {
        hit = rhit;
    }

    return leftHit || rightHit;
}

const BBox &BVHNode::bbox() const
{
    return m_bbox;
}

const Vec3d &BVHNode::centroid() const
{
    return m_bbox.centroid();
}

BVH::BVH(std::vector<Shape *> &shapes) : head(new BVHNode(shapes))
{
}