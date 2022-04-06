#ifndef _CAMERA_REECE_
#define _CAMERA_REECE_

#include <string>
#include <vector>

#include "Vector3.hpp"
#include "CoordSys.hpp"
#include "Ray.hpp"

class Camera
{
public:
  const static double DEFAULT_IMAGE_WIDTH;
  const static double DEFAULT_ASPECT_RATIO;

  Camera();
  Camera(const Vec3d &position, const Vec3d &viewDir, const double imagePlaneWidth = DEFAULT_IMAGE_WIDTH, const double aspectRatio = DEFAULT_ASPECT_RATIO);

  virtual ~Camera() {}

  CoordSys basis() const;
  double imagePlaneWidth() const;
  double imagePlaneHeight() const;

  void setImagePixels(const size_t x, const size_t y);

  virtual Ray generateRay(const size_t i, const size_t j) const = 0;

protected:
  size_t m_pixelsX = 0, m_pixelsY = 0;
  double m_imagePlaneWidth, m_imagePlaneHeight;
  CoordSys m_basis;
};

#endif