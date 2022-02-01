#ifndef _PERSPECTIVE_CAMERA_REECE_
#define _PERSPECTIVE_CAMERA_REECE_

#include "Camera.hpp"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera() = default;
  PerspectiveCamera(const std::string &name, const CoordinateSys &basis, const double focalLength);

  virtual Ray generateRay(const size_t i, const size_t j) const;

private:
  double m_focalLength;
};

#endif