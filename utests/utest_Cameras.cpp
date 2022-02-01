#include <iostream>

#include "Camera.hpp"
#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"
#include "CoordinateSys.hpp"
#include "Framebuffer.hpp"
#include "Shape.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"

int main()
{
  // CoordinateSys ori = CoordinateSys::global;
  Vec3d u, v, w;
  const double pi = 2 * acos(0.0);
  const double angle = 0 * pi / 180;
  u = Vec3d(cos(angle), 0, sin(angle));
  w = Vec3d(sin(angle), 0, cos(angle));
  // v = Vec3d(cos(angle + pi / 2), sin(angle + pi / 2), 0);
  u = u.unitize();
  w = w.unitize();
  v = -u.cross(w);
  // v = v.unitize();
  // w = u.cross(v);
  CoordinateSys ori(Vec3d(-0.1, 0, -0.25), u, v, -w);
  std::cout << "u: " << u << std::endl
            << "v: " << v << std::endl
            << "w: " << w << std::endl;
  Camera *camera;
  camera = new PerspectiveCamera("camera", ori, 1.0);
  // camera = new OrthographicCamera("camera", ori);
  camera->m_pixels_x = 200;
  camera->m_pixels_y = 200;
  camera->m_image_w = 1;
  camera->m_image_h = 1;

  Framebuffer f(camera->m_pixels_x, camera->m_pixels_y);
  Triangle t(Vec3d(0.25, 0.25, 3), Vec3d(-0.25, 0.5, 2.75), Vec3d(0, -0.1, 3.25));
  Sphere s(Vec3d(0.06, 0, 7), 0.5);
  // std::vector<Shape *> shapes({ &t, &s });

  for (size_t i = 0; i < camera->m_pixels_x; ++i) {
    for (size_t j = 0; j < camera->m_pixels_y; ++j) {
      auto r = camera->generateRay(i, j);

      double triT, sphT;

      bool tHit(t.closestHit(r, 0, INFINITY, triT));
      bool sHit(s.closestHit(r, 0, INFINITY, sphT));

      Vec3f color;
      if (sHit && tHit) {
        if (triT < sphT) {
          color = Vec3f(0, 1, 0);
        } else {
          color = Vec3f(0, 0, 1);
        }
      } else {
        color = Vec3f(0, tHit ? 1 : 0, sHit ? 1 : 0);
      }

      f.setPixelColor(i, j, color);
    }
  }

  f.exportAsPNG("utest_Cameras.test.png");
  return 0;
}