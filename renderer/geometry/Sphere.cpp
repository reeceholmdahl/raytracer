#include "Sphere.hpp"
#include "CoordinateSys.hpp"

Sphere::Sphere()
    : Sphere(Vec3d(0, 0, -2), 0.25)
{
}

Sphere::Sphere(const Vec3d &position, const double radius)
    : m_position(position), m_radius(radius)
{
}

bool Sphere::closestHit(const Ray &r, const double tmin, const double tmax, double &t) const
{
  // discriminant b^2-4ac, negative no solutions, zero one solution, positive two solutions
  auto eminusc(r.origin() - m_position);
  auto d(r.direction());
  double discriminant(pow(d.dot(eminusc), 2) - d.dot(d) * (eminusc.dot(eminusc) - m_radius * m_radius));

  if (discriminant < 0)
    return false;

  double num((-d).dot(eminusc));
  double denom(d.dot(d));
  if (discriminant == 0.0)
  {
    double t1 = num / denom;
    if (t < tmin || t > tmax)
      return false;
    t = t1;
  }
  else
  {
    double t1((num + sqrt(discriminant)) / denom);
    double t2((num - sqrt(discriminant)) / denom);

    if ((t1 < tmin && t2 < tmin) || (t1 > tmax && t2 > tmax))
      return false;
    t = std::min(t1, t2);
  }

  return true;
}

bool Sphere::closestHit(const Ray &r) const
{
  double t;
  return closestHit(r, 0, INFINITY, t);
}

Vec3d Sphere::normal(const Vec3d &position) const
{
  Vec3d localPos((position - m_position));

  return localPos.unitize();
}