#include <vector>
#include <algorithm>

#include "Triangle.hpp"

// TODO move these to constants
Triangle::Triangle()
  : Triangle(Vec3d(-0.25, -0.25, -2), Vec3d(0.25, -0.25, -2),
             Vec3d(0, 0.25, -2))
{
}

Triangle::Triangle(const Vec3d& a, const Vec3d& b, const Vec3d& c)
  : Shape("tri")
  , m_a(a)
  , m_b(b)
  , m_c(c)
{
  auto U(m_b - m_a);
  auto V(m_c - m_a);
  m_normal = U.cross(V).unitize();

  auto minx = std::min({ a[0], b[0], c[0] });
  auto maxx = std::max({ a[0], b[0], c[0] });
  auto miny = std::min({ a[1], b[1], c[1] });
  auto maxy = std::max({ a[1], b[1], c[1] });
  auto minz = std::min({ a[2], b[2], c[2] });
  auto maxz = std::max({ a[2], b[2], c[2] });

  m_bbox = BBox(Vec3d(minx - 0.1, miny - 0.1, minz - 0.1),
                Vec3d(maxx + 0.1, maxy + 0.1, maxz + 0.1));
}

bool
Triangle::closestHit(const Ray& r, HitStruct& hit) const
{
  // e = r.origin, d = r.direction
  // triangle with vertices a, b, c
  // e + td = a + B(b-a) + Y(b-c) for some intersectT > 0, B > 0, Y > 0, and B+Y
  // < 1
  // Following code is based directly off cramer's rule in the book
  // This is made to get a quick and dirty attempt at ray tracing a triangle
  // Code can be heavily optimized

  std::vector<double> matrixA(9), matrixBeta(9), matrixGamma(9), matrixT(9);

  matrixA = { // 1st row
              m_a[0] - m_b[0], m_a[0] - m_c[0], r.direction()[0],
              // 2nd row
              m_a[1] - m_b[1], m_a[1] - m_c[1], r.direction()[1],
              // 3rd row
              m_a[2] - m_b[2], m_a[2] - m_c[2], r.direction()[2]
  };

  double detA =
    matrixA[0] * (matrixA[4] * matrixA[8] - matrixA[5] * matrixA[7]) +
    matrixA[3] * (matrixA[2] * matrixA[7] - matrixA[1] * matrixA[8]) +
    matrixA[6] * (matrixA[1] * matrixA[5] - matrixA[4] * matrixA[2]);

  matrixT = {
    // 1st row
    m_a[0] - m_b[0], m_a[0] - m_c[0], m_a[0] - r.origin()[0],
    // 2nd row
    m_a[1] - m_b[1], m_a[1] - m_c[1], m_a[1] - r.origin()[1],
    // 3rd row
    m_a[2] - m_b[2], m_a[2] - m_c[2], m_a[2] - r.origin()[2],
  };

  double detT =
    matrixT[0] * (matrixT[4] * matrixT[8] - matrixT[5] * matrixT[7]) +
    matrixT[3] * (matrixT[2] * matrixT[7] - matrixT[1] * matrixT[8]) +
    matrixT[6] * (matrixT[1] * matrixT[5] - matrixT[4] * matrixT[2]);

  double intersectT = detT / detA;

  if (intersectT < hit.tmin || intersectT > hit.tmax)
    return false;

  matrixGamma = { // 1st row
                  m_a[0] - m_b[0], m_a[0] - r.origin()[0], r.direction()[0],
                  // 2nd row
                  m_a[1] - m_b[1], m_a[1] - r.origin()[1], r.direction()[1],
                  // 3rd row
                  m_a[2] - m_b[2], m_a[2] - r.origin()[2], r.direction()[2]
  };

  double detGamma =
    matrixGamma[0] *
      (matrixGamma[4] * matrixGamma[8] - matrixGamma[5] * matrixGamma[7]) +
    matrixGamma[3] *
      (matrixGamma[2] * matrixGamma[7] - matrixGamma[1] * matrixGamma[8]) +
    matrixGamma[6] *
      (matrixGamma[1] * matrixGamma[5] - matrixGamma[4] * matrixGamma[2]);

  double gamma = detGamma / detA;

  if (gamma < 0 || gamma > 1)
    return false;

  matrixBeta = { // 1st row
                 m_a[0] - r.origin()[0], m_a[0] - m_c[0], r.direction()[0],
                 // 2nd row
                 m_a[1] - r.origin()[1], m_a[1] - m_c[1], r.direction()[1],
                 // 3rd row
                 m_a[2] - r.origin()[2], m_a[2] - m_c[2], r.direction()[2]
  };

  double detBeta =
    matrixBeta[0] *
      (matrixBeta[4] * matrixBeta[8] - matrixBeta[5] * matrixBeta[7]) +
    matrixBeta[3] *
      (matrixBeta[2] * matrixBeta[7] - matrixBeta[1] * matrixBeta[8]) +
    matrixBeta[6] *
      (matrixBeta[1] * matrixBeta[5] - matrixBeta[4] * matrixBeta[2]);

  double beta = detBeta / detA;

  if (beta < 0 || beta > 1 - gamma)
    return false;

  hit.ray = r;
  hit.shaderPtr = shaderPtr;
  hit.shape = this;
  hit.t = intersectT;
  hit.normal = normal();

  return true;
}

const Vec3d&
Triangle::normal() const
{
  return m_normal;
}