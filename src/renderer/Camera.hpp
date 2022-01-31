#ifndef _CAMERA_REECE_
#define _CAMERA_REECE_

#include <string>

#include "Vector3.hpp"
#include "CoordinateSys.hpp"

class Camera
{
public:
  Camera() = default;
  virtual ~Camera() {}

  virtual Vec3d position() const = 0;
  virtual CoordinateSys basis() const = 0;
  virtual std::string name() const = 0;
};

#endif