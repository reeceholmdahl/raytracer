#include "Vector3.hpp"
#include "CoordinateSys.hpp"
#include "PerspectiveCamera.hpp"
#include "Framebuffer.hpp"
#include "handleGraphicsArgs.h"

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  const size_t nx(args.width), ny(args.height);

  Framebuffer fb(nx, ny);

  Camera *cam;
  cam = new PerspectiveCamera("persp", CoordinateSys::global, 2.0);
  cam->set_pixels_x(nx);
  cam->set_pixels_y(ny);
  cam->set_image_w(1.0);
  cam->set_image_h(1.0 * ny / nx);

  for (size_t i = 0; i < nx; ++i) {
    for (size_t j = 0; j < ny; ++j) {
      auto r = cam->generateRay(i, j);

      Vec3f color(Vec3f(0.5, 0.5, -2 + (0.5 + r.direction()[0]) * (0.5 + r.direction()[1])) + r.direction());
      fb.setPixelColor(i, j, color);
    }
  }

  fb.exportAsPNG("utest_RayDirectionColor.test.png");

  return 0;
}