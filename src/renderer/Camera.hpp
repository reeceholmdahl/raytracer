#ifndef _CAMERA_REECE_
#define _CAMERA_REECE_

#include <string>
#include <vector>

#include "Vector3.hpp"
#include "CoordinateSys.hpp"
#include "Ray.hpp"

class Camera
{
public:
  // Temporary/unsure
  size_t m_pixels_x, m_pixels_y;
  double m_image_w, m_image_h;

  Camera() = default;
  Camera(const std::string &name, const CoordinateSys &basis);
  virtual ~Camera() {}

  virtual CoordinateSys basis() const;
  virtual std::string name() const;

  virtual Ray generateRay(const size_t i, const size_t j) const = 0;

private:
  std::string m_name;
  CoordinateSys m_basis;
};

#endif