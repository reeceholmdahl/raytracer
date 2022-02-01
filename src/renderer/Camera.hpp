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
  Camera() = default;
  Camera(const std::string &name, const Vec3d &position, const CoordinateSys &basis);
  virtual ~Camera() {}

  virtual Vec3d position() const;
  virtual CoordinateSys basis() const;
  virtual std::string name() const;

  virtual std::vector<Ray> generateRays() const = 0;

private:
  std::string m_name;
  Vec3d m_position;
  CoordinateSys m_basis;
};

#endif