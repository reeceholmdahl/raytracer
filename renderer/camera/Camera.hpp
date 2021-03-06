#ifndef _CAMERA_REECE_
#define _CAMERA_REECE_

#include <string>
#include <vector>

#include "Constants.h"
#include "CoordSys.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

class Camera
{
public:
  Camera() = delete;
  Camera(const Vec3d& position,
         const Vec3d& viewDir,
         const double imagePlaneWidth,
         const double aspectRatio)
    : m_imagePlaneWidth(imagePlaneWidth)
    , m_imagePlaneHeight(imagePlaneWidth / aspectRatio)
    , m_basis(CoordSys(position, viewDir))
  {
    left = -m_imagePlaneWidth / 2.;
    right = m_imagePlaneWidth / 2.;
    bottom = -m_imagePlaneHeight / 2.;
    top = m_imagePlaneHeight / 2.;
  }

  virtual ~Camera() {}

  virtual Ray generateRay(const size_t i,
                          const size_t j,
                          const double di = 0.5,
                          const double dj = 0.5) const = 0;

  const CoordSys& basis() const { return m_basis; }

  double imagePlaneWidth() const { return m_imagePlaneWidth; }

  double imagePlaneHeight() const { return m_imagePlaneHeight; }

  void setImagePixels(const size_t x, const size_t y)
  {
    m_pixelsX = x;
    m_pixelsY = y;
  }

protected:
  void genUV(double& u,
             double& v,
             const size_t i,
             const size_t j,
             const double di,
             const double dj) const
  {
    u = left + (right - left) * (i + di) / static_cast<double>(m_pixelsX);
    v = bottom + (top - bottom) * (j + dj) / static_cast<double>(m_pixelsY);
  }

  size_t m_pixelsX = 0, m_pixelsY = 0;
  double m_imagePlaneWidth = -1, m_imagePlaneHeight = -1, left, right, top,
         bottom;
  CoordSys m_basis;
};

#endif