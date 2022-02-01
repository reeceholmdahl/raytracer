#include <iostream>

#include "Camera.hpp"
#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"
#include "CoordinateSys.hpp"
#include "Framebuffer.hpp"
#include "Triangle.hpp"

int main()
{
  // CoordinateSys ori = CoordinateSys::global;
  Vec3d u, v, w;
  const double pi = 2 * acos(0.0);
  const double angle = 0 * pi / 180;
  u = Vec3d(cos(angle), 0, sin(angle));
  w = -Vec3d(sin(angle), 0, cos(angle));
  // v = Vec3d(cos(angle + pi / 2), sin(angle + pi / 2), 0);
  u = u.unitize();
  w = w.unitize();
  v = u.cross(w);
  // v = v.unitize();
  // w = u.cross(v);
  CoordinateSys ori(Vec3d(), u, v, w);
  std::cout << "u: " << u << std::endl
            << "v: " << v << std::endl
            << "w: " << w << std::endl;
  Camera *camera;
  camera = new PerspectiveCamera("camera", ori, 1.0);
  // camera = new OrthographicCamera("camera", ori);
  camera->m_pixels_x = 300;
  camera->m_pixels_y = 300;
  camera->m_image_w = 1;
  camera->m_image_h = 1;

  Framebuffer f(camera->m_pixels_x, camera->m_pixels_y);
  Triangle t(Vec3d(0.25, 0.25, 2), Vec3d(-0.25, 0.5, 1.75), Vec3d(0, -0.1, 2.25));

  for (size_t i = 0; i < camera->m_pixels_x; ++i) {
    for (size_t j = 0; j < camera->m_pixels_y; ++j) {
      auto r = camera->generateRay(i, j);
      Vec3f color(t.closestHit(r) ? Vec3f(0, 1, 0) : Vec3f());
      // std::cout << i << "x+" << j << "y: " << color << std::endl;
      f.setPixelColor(i, j, color);
    }
  }

  f.exportAsPNG("utest_Cameras.test.png");
  return 0;
}