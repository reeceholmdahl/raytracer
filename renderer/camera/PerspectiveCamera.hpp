#ifndef _PERSPECTIVE_CAMERA_REECE_
#define _PERSPECTIVE_CAMERA_REECE_

#include "Camera.hpp"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera() = default;
  PerspectiveCamera(const std::string &name, const CoordinateSys &basis, const double focalLength);
  PerspectiveCamera(const std::string &name, const CoordinateSys &basis, const double focalLength, const size_t pixels_x, const size_t pixels_y, const double image_w, const double image_h);

  virtual Ray generateRay(const size_t i, const size_t j) const;

private:
  double m_focalLength;
};

#endif