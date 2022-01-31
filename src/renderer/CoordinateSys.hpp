#ifndef _COORDINATE_SYS_REECE_
#define _COORDINATE_SYS_REECE_

#include "Vector3.hpp"

class CoordinateSys
{
public:
  CoordinateSys(const Vec3d &basis);

private:
  Vec3d m_basis;
};

#endif