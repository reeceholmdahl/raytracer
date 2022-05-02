#include "Sphere.hpp"

// TODO move these to constants
Sphere::Sphere()
  : Sphere(Vec3d(0, 0, -2), 0.25)
{
}

Sphere::Sphere(const Vec3d& position, const double radius)
  : Shape("sphere")
  , m_position(position)
  , m_radius(radius)
  , m_bbox(BBox(m_position - Vec3d(m_radius, m_radius, m_radius),
                m_position + Vec3d(m_radius, m_radius, m_radius)))
{
}

bool
Sphere::closestHit(const Ray& r, HitStruct& hit) const
{
  hit.ray = r;
  hit.shaderPtr = shaderPtr;
  hit.shape = this;
  // std::cout << "After ray and shaderptr assignment" << std::endl;

  // discriminant b^2-4ac, negative no solutions, zero one solution, positive
  // two solutions
  auto eminusc(r.origin() - m_position);
  auto d(r.direction());
  double discriminant(pow(d.dot(eminusc), 2) -
                      d.dot(d) * (eminusc.dot(eminusc) - m_radius * m_radius));

  if (discriminant < 0)
    return false;

  double num((-d).dot(eminusc));
  double denom(d.dot(d));
  if (discriminant == 0.0) {
    double t1 = num / denom;
    if (t1 < hit.tmin || t1 > hit.tmax)
      return false;
    hit.t = t1;
  } else {
    double t1((num + sqrt(discriminant)) / denom);
    double t2((num - sqrt(discriminant)) / denom);

    if ((t1 < hit.tmin && t2 < hit.tmin) || (t1 > hit.tmax && t2 > hit.tmax))
      return false;
    hit.t = std::min(t1, t2);
  }

  hit.normal = normal(r.point(hit.t));

  return true;
}

Vec3d
Sphere::normal(const Vec3d& position) const
{
  Vec3d localPos((position - m_position));

  return localPos.unitize();
}