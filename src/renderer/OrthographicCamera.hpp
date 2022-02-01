#ifndef _ORTHOGRAPHIC_CAMERA_REECE_
#define _ORTHOGRAPHIC_CAMERA_REECE_

#include "Camera.hpp"
#include "Vector3.hpp"
#include "CoordinateSys.hpp"

class OrthographicCamera : public Camera
{
public:
  OrthographicCamera() = default;
  OrthographicCamera(const std::string &name, const CoordinateSys &basis);

  // virtual Vec3d position() const;
  // virtual CoordinateSys basis() const;
  // virtual std::string name() const;

  virtual Ray generateRay(const size_t i, const size_t j) const;
};

#endif