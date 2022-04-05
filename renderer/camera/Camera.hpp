#ifndef _CAMERA_REECE_
#define _CAMERA_REECE_

#include <string>
#include <vector>

#include "Vector3.hpp"
#include "CoordSys.hpp"
#include "Ray.hpp"

class Camera
{
public:
  const static size_t DEFAULT_PIXELS_XY;
  const static double DEFAULT_IMAGE_WH;

  Camera(const std::string &name);
  Camera(const std::string &name, const CoordSys &basis);
  Camera(const std::string &name, const CoordSys &basis, const size_t pixels_x, const size_t pixels_y, const double image_w, const double image_h);
  virtual ~Camera() {}

  CoordSys basis() const;
  std::string name() const;
  size_t pixels_x() const;
  size_t pixels_y() const;
  double image_w() const;
  double image_h() const;

  void set_pixels_x(const size_t pixels_x);
  void set_pixels_y(const size_t pixels_y);
  void set_image_w(const double width);
  void set_image_h(const double height);

  virtual Ray generateRay(const size_t i, const size_t j) const = 0;

private:
  std::string m_name;
  CoordSys m_basis;
  size_t m_pixels_x, m_pixels_y;
  double m_image_w, m_image_h;
};

#endif