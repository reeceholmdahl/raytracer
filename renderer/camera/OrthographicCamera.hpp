#ifndef RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_H_
#define RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_H_

#include "Camera.hpp"
#include "Vector3.hpp"
#include "CoordSys.hpp"

class OrthographicCamera : public Camera
{
public:
  OrthographicCamera(
      const Vec3d &position = renderer::constants::DEFAULT_CAMERA_POS,
      const Vec3d &viewDir = renderer::constants::DEFAULT_VIEW_DIR,
      const double imagePlaneWidth = renderer::constants::DEFAULT_IMAGE_WIDTH,
      const double aspectRatio = renderer::constants::DEFAULT_ASPECT_RATIO);

  virtual Ray generateRay(const size_t i, const size_t j) const;
};

#endif