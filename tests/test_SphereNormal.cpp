#include <iostream>

#include "boost/filesystem.hpp"

#include "renderer.hpp"
#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "Vector3.hpp"
#include "CoordinateSys.hpp"
#include "Framebuffer.hpp"
#include "Sphere.hpp"

#include "handleGraphicsArgs.h"

using namespace renderer;

namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  // Used cmdline arguments
  const size_t nx(args.width), ny(args.height);
  const fs::path outdir(args.outputDirectory);

  if (!fs::exists(outdir))
  {
    std::cout << "Creating directory " << outdir.string() << std::endl;
    fs::create_directories(outdir);
  }

  Framebuffer fb(nx, ny);

  Sphere sph;

  Camera *cam = new PerspectiveCamera();

  cam->set_pixels_x(nx);
  cam->set_pixels_y(ny);

  for (size_t i(0); i < nx; ++i)
  {
    for (size_t j(0); j < ny; ++j)
    {
      auto ray(cam->generateRay(i, j));

      auto hit = HitStruct();

      Vec3f color(0.1, 0.1, 0.1);
      if (sph.closestHit(ray, 0, INFINITY, hit))
      {
        auto normal(sph.normal(hit.hitPoint()));

        // normal shading
        color = normal;
        color += Vec3f(1.0, 1.0, 1.0);
        color /= 2;
      }

      fb.setPixelColor(i, j, color);
    }
  }

  fb.exportAsPNG((outdir / "test_SphereNormal.test.png").string());

  return 0;
}