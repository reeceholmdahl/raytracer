#include <iostream>

#include "Camera.hpp"
#include "OrthographicCamera.hpp"
#include "CoordinateSys.hpp"
#include "Framebuffer.hpp"

int main()
{
  CoordinateSys ori = CoordinateSys::global;
  Vec3d u, v, w;
  const double pi = 2 * acos(0.0);
  const double angle = 0;
  u = Vec3d(cos(angle), sin(angle), 0);
  v = Vec3d(cos(angle + pi / 2), sin(angle + pi / 2), 0);
  u = u.unitize();
  v = v.unitize();
  w = u.cross(v);
  std::cout << "u: " << u << std::endl
            << "v: " << v << std::endl
            << "w: " << w << std::endl;
  // CoordinateSys ori(Vec3d(0, 0, 0), u, v, w);
  OrthographicCamera oc("ortho", ori);
  oc.m_pixels_x = 100;
  oc.m_pixels_y = 100;
  oc.m_image_w = 1;
  oc.m_image_h = 1;

  Framebuffer f(oc.m_pixels_x, oc.m_pixels_y);

  for (size_t i = 0; i < oc.m_pixels_x; ++i) {
    for (size_t j = 0; j < oc.m_pixels_y; ++j) {
      auto r = oc.generateRay(i, j);
      Vec3f color((r.origin() + Vec3f(sqrt(2.) / 2, sqrt(2.) / 2, 0)) / (sqrt(2.)));
      std::cout << i << "x+" << j << "y: " << color << std::endl;
      f.setPixelColor(i, j, color);
    }
  }

  f.exportAsPNG("utest_Cameras.test.png");
  return 0;
}