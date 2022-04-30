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
  Camera();
  Camera(
      const Vec3d &position = renderer::constants::DEFAULT_CAMERA_POS,
      const Vec3d &viewDir = renderer::constants::DEFAULT_VIEW_DIR,
      const double imagePlaneWidth = renderer::constants::DEFAULT_IMAGE_WIDTH,
      const double aspectRatio = renderer::constants::DEFAULT_ASPECT_RATIO);

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