#ifndef RENDERER_CAMERA_PERSPECTIVE_CAMERA_H_
#define RENDERER_CAMERA_PERSPECTIVE_CAMERA_H_

#include "Camera.hpp"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera(
    const Vec3d& position = renderer::constants::DEFAULT_CAMERA_POS,
    const Vec3d& viewDir = renderer::constants::DEFAULT_VIEW_DIR,
    const double focalLength = renderer::constants::DEFAULT_FOCAL_LENGTH,
    const double imagePlaneWidth = renderer::constants::DEFAULT_IMAGE_WIDTH,
    const double aspectRatio = renderer::constants::DEFAULT_ASPECT_RATIO)
    : Camera(position, viewDir, imagePlaneWidth, aspectRatio)
    , m_focalLength(focalLength)
  {
  }

  virtual Ray generateRay(const size_t i,
                          const size_t j,
                          const double di,
                          const double dj) const;

private:
  double m_focalLength;
};

#endif