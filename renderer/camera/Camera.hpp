#ifndef _CAMERA_REECE_
#define _CAMERA_REECE_

#include <string>
#include <vector>

#include "Constants.hpp"
#include "Vector3.hpp"
#include "CoordSys.hpp"
#include "Ray.hpp"

class Camera
{
public:
  Camera() = delete;
  Camera(const Vec3d& position, const Vec3d& viewDir,
         const double imagePlaneWidth, const double aspectRatio);

  virtual ~Camera() {}

  virtual Ray generateRay(const size_t i, const size_t j) const = 0;

  inline const CoordSys& basis() const { return m_basis; }

  inline double imagePlaneWidth() const { return m_imagePlaneWidth; }

  inline double imagePlaneHeight() const { return m_imagePlaneHeight; }

  inline void setImagePixels(const size_t x, const size_t y)
  {
    m_pixelsX = x;
    m_pixelsY = y;
  }

protected:
  inline void genUV(double& u, double& v, const size_t i, const size_t j) const
  {
    u = left + (right - left) * (i + 0.5) / static_cast<double>(m_pixelsX);
    v = bottom + (top - bottom) * (j + 0.5) / static_cast<double>(m_pixelsY);
  }

  size_t m_pixelsX = 0, m_pixelsY = 0;
  double m_imagePlaneWidth = -1, m_imagePlaneHeight = -1, left, right, top,
         bottom;
  CoordSys m_basis;
};

#endif