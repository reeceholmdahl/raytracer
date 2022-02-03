#include "Sphere.hpp"
#include "CoordinateSys.hpp"

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
  // x = < rcos(theta)sin(phi), rsin(theta)sin(phi), rcos(phi) >
  // n = < r^2cos(theta)sin^2(phi), r^2sin(theta)sin^2(phi), -r^2sin(phi)cos(phi) >

  Vec3d localPos((position - m_position));

  // double phi(-acos(localPos[2] / m_radius));
  // double theta(-acos(localPos[0] / (m_radius * sin(phi))));

  // double r2(m_radius * m_radius);

  // Vec3d n(
  //   r2 * cos(theta) * pow(sin(phi), 2),// should be positive
  //   r2 * sin(theta) * pow(sin(phi), 2),// should be positive
  //   r2 * sin(phi) * cos(phi));// should be negative

  // |n|=r^2sin(phi), can just divide
  // return n.unitize();
  // return n /= (r2 * sin(phi));
  return localPos.unitize();
}