#ifndef _ORTHOGRAPHIC_CAMERA_REECE_
#define _ORTHOGRAPHIC_CAMERA_REECE_

#include "Camera.hpp"
#include "Vector3.hpp"
#include "CoordinateSys.hpp"

class OrthographicCamera : public Camera
{
public:
  OrthographicCamera();
  OrthographicCamera(const std::string &name);
  OrthographicCamera(const std::string &name, const CoordinateSys &basis);
  OrthographicCamera(const std::string &name, const CoordinateSys &basis, const size_t pixels_x, const size_t pixels_y, const double image_w, const double image_h);

  virtual Ray generateRay(const size_t i, const size_t j) const;
};

#endif