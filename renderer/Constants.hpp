#ifndef RENDERER_CONSTANTS_H_
#define RENDERER_CONSTANTS_H_

#include "Vector3.hpp"

namespace renderer {
namespace constants {
const size_t DEFAULT_WIDTH(100);
const size_t DEFAULT_HEIGHT(100);
const double DEFAULT_IMAGE_WIDTH(0.5);
const double DEFAULT_ASPECT_RATIO(1.0);
const double DEFAULT_FOCAL_LENGTH(1.0);
const Vec3d DEFAULT_CAMERA_POS(0, 0, 0);
const Vec3d DEFAULT_VIEW_DIR(0, 0, -1);
const Vec3f DEFAULT_BG_COLOR(0.198, 0.198, 0.198);
const Vec3f DEFAULT_AMBIENT(0.0, 0.0, 0.0);
const Vec3f DEFAULT_DIFFUSE(1, 0, 1);
const Vec3f DEFAULT_SPECULAR(0, 0, 1);
const double DEFAULT_PHONG_EXP(1);
}
}

#endif