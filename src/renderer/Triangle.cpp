#include <vector>

#include "Triangle.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

Triangle::Triangle(const Vec3d &a, const Vec3d &b, const Vec3d &c)
  : m_a(a), m_b(b), m_c(c)
{
}

bool Triangle::closestHit(const Ray &r) const
{
  // e = r.origin, d = r.direction
  // triangle with vertices a, b, c
  // e + td = a + B(b-a) + Y(b-c) for some t > 0, B > 0, Y > 0, and B+Y < 1
  // Following code is based directly off cramer's rule in the book
  // This is made to get a quick and dirty attempt at ray tracing a triangle
  // Code can be heavily optimized

  std::vector<double> matrixA(9), matrixBeta(9), matrixGamma(9), matrixT(9);

  matrixA = {
    // 1st row
    m_a[0] - m_b[0],
    m_a[0] - m_c[0],
    r.direction()[0],
    // 2nd row
    m_a[1] - m_b[1],
    m_a[1] - m_c[1],
    r.direction()[1],
    // 3rd row
    m_a[2] - m_b[2],
    m_a[2] - m_c[2],
    r.direction()[2]
  };

  double detA = matrixA[0] * (matrixA[4] * matrixA[8] - matrixA[5] * matrixA[7])
                + matrixA[3] * (matrixA[2] * matrixA[7] - matrixA[1] * matrixA[8])
                + matrixA[6] * (matrixA[1] * matrixA[5] - matrixA[4] * matrixA[2]);

  matrixT = {
    // 1st row
    m_a[0] - m_b[0],
    m_a[0] - m_c[0],
    m_a[0] - r.origin()[0],
    // 2nd row
    m_a[1] - m_b[1],
    m_a[1] - m_c[1],
    m_a[1] - r.origin()[1],
    // 3rd row
    m_a[2] - m_b[2],
    m_a[2] - m_c[2],
    m_a[2] - r.origin()[2],
  };

  double detT = matrixT[0] * (matrixT[4] * matrixT[8] - matrixT[5] * matrixT[7])
                + matrixT[3] * (matrixT[2] * matrixT[7] - matrixT[1] * matrixT[8])
                + matrixT[6] * (matrixT[1] * matrixT[5] - matrixT[4] * matrixT[2]);

  double t = detT / detA;

  if (t < 0) return false;

  matrixGamma = {
    // 1st row
    m_a[0] - m_b[0],
    m_a[0] - r.origin()[0],
    r.direction()[0],
    // 2nd row
    m_a[1] - m_b[1],
    m_a[1] - r.origin()[1],
    r.direction()[1],
    // 3rd row
    m_a[2] - m_b[2],
    m_a[2] - r.origin()[2],
    r.direction()[2]
  };

  double detGamma = matrixGamma[0] * (matrixGamma[4] * matrixGamma[8] - matrixGamma[5] * matrixGamma[7])
                    + matrixGamma[3] * (matrixGamma[2] * matrixGamma[7] - matrixGamma[1] * matrixGamma[8])
                    + matrixGamma[6] * (matrixGamma[1] * matrixGamma[5] - matrixGamma[4] * matrixGamma[2]);

  double gamma = detGamma / detA;

  if (gamma < 0 || gamma > 1) return false;

  matrixBeta = {
    // 1st row
    m_a[0] - r.origin()[0],
    m_a[0] - m_c[0],
    r.direction()[0],
    // 2nd row
    m_a[1] - r.origin()[1],
    m_a[1] - m_c[1],
    r.direction()[1],
    // 3rd row
    m_a[2] - r.origin()[2],
    m_a[2] - m_c[2],
    r.direction()[2]
  };

  double detBeta = matrixBeta[0] * (matrixBeta[4] * matrixBeta[8] - matrixBeta[5] * matrixBeta[7])
                   + matrixBeta[3] * (matrixBeta[2] * matrixBeta[7] - matrixBeta[1] * matrixBeta[8])
                   + matrixBeta[6] * (matrixBeta[1] * matrixBeta[5] - matrixBeta[4] * matrixBeta[2]);

  double beta = detBeta / detA;

  if (beta < 0 || beta > 1 - gamma) return false;

  return true;
}