#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(const std::string &name, const Vec3d &position, const CoordinateSys &basis)
  : Camera(name, position, basis)
{
}