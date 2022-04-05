#ifndef RENDERER_CAMERA_PERSPECTIVE_CAMERA_H_
#define RENDERER_CAMERA_PERSPECTIVE_CAMERA_H_

#include "Camera.hpp"

class PerspectiveCamera : public Camera
{
public:
  const static double DEFAULT_FOCAL_LENGTH;

  PerspectiveCamera();
  PerspectiveCamera(const std::string &name);
  PerspectiveCamera(const std::string &name, const CoordSys &basis, const double focalLength);
  PerspectiveCamera(const std::string &name, const CoordSys &basis, const double focalLength, const size_t pixels_x, const size_t pixels_y, const double image_w, const double image_h);

  virtual Ray generateRay(const size_t i, const size_t j) const;

private:
  double m_focalLength;
};

#endif