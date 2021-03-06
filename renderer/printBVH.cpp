#include "BVH.hpp"

void
BVH::print(const std::string& prefix, Shape* node, bool isLeft,
           const std::ostream& os) const
{
  if (node) {
    if (node->type() == "bvh node") {
      std::cout << prefix;

      std::cout << (isLeft ? "|--" : "*--");

      // print the value of the node
      std::cout << node->type() << " bbox: " << node->bbox().minPt() << " to "
                << node->bbox().maxPt() << std::endl;

      auto bvhNode = dynamic_cast<BVHNode*>(node);

      // enter the next tree level - left and right branch
      print(prefix + (isLeft ? "|   " : "    "), bvhNode->left, true, os);
      print(prefix + (isLeft ? "|   " : "    "), bvhNode->right, false, os);
    } else {
      std::cout << prefix;

      std::cout << (isLeft ? "|--" : "*--");

      // print the value of the node
      std::cout << node->type() << " name: " << node->name()
                << " shader: " << node->shaderPtr->name() << std::endl;
      // << " bbox: " << node->bbox().minPt() << " to " << node->bbox().maxPt()
      // << std::endl;
    }
  } else {
    std::cout << prefix;

    std::cout << (isLeft ? "|--" : "*--");

    // print the value of the node
    std::cout << "no shape" << std::endl;
  }
}