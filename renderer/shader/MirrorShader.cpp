#include "MirrorShader.hpp"
#include "Light.hpp"
#include "Scene.hpp"

Vec3f
MirrorShader::apply(const HitStruct& hit) const
{
  Vec3f color;

  if (hit.depth < hit.scene->recursionDepth) {
    Vec3d incoming((hit.ray.origin() - hit.hitPoint())),
      outgoing(hit.normal * (2 * incoming.dot(hit.normal)) - incoming);

    Ray ray(hit.hitPoint(), outgoing.unitize());
    HitStruct nextHit(renderer::constants::VERY_SMALL, INFINITY, hit.scene,
                      hit.depth + 1);
    if (hit.scene->closestHit(ray, nextHit) && hit.shaderPtr) {
      color = nextHit.shaderPtr->apply(nextHit);
    } else {
      color = hit.scene->bgColor;
    }
  } else {
    color = m_ambient;
  }

  return color;
}