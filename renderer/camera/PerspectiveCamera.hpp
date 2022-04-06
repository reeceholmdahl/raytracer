#ifndef RENDERER_CAMERA_PERSPECTIVE_CAMERA_H_
#define RENDERER_CAMERA_PERSPECTIVE_CAMERA_H_

#include "Camera.hpp"
#include "Vector3.hpp"

class PerspectiveCamera : public Camera
{
public:
  const static double DEFAULT_FOCAL_LENGTH;

  PerspectiveCamera(const Vec3d &position = Vec3d(), const Vec3d &viewDir = Vec3d(0, 0, 1), const double focalLength = PerspectiveCamera::DEFAULT_FOCAL_LENGTH, const double imagePlaneWidth = Camera::DEFAULT_IMAGE_WIDTH, const double aspectRatio = Camera::DEFAULT_ASPECT_RATIO);

  virtual Ray generateRay(const size_t i, const size_t j) const;

private:
  double m_focalLength;
};

#endif