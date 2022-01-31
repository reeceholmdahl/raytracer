#ifndef _CAMERA_REECE_
#define _CAMERA_REECE_

#include <string>

#include "Vector3.hpp"

class Camera
{
public:
  Camera();
  virtual ~Camera() {}

private:
  Vec3d position, basis;
  std::string name;
};

#endif