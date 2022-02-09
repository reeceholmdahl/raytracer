#include <iostream>

#include <boost/filesystem.hpp>

#include "renderer.hpp"
#include "Vector3.hpp"
#include "CoordinateSys.hpp"
#include "PerspectiveCamera.hpp"
#include "Framebuffer.hpp"
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

  Camera *cam;
  cam = new PerspectiveCamera();
  cam->set_pixels_x(nx);
  cam->set_pixels_y(ny);

  for (size_t i = 0; i < nx; ++i)
  {
    for (size_t j = 0; j < ny; ++j)
    {
      auto r = cam->generateRay(i, j);

      Vec3f color((Vec3f(1, 1, 0) + r.direction().unitize()) / 2);
      color[2] = 0;
      fb.setPixelColor(i, j, color);
    }
  }

  fb.exportAsPNG((outdir / "test_RayDirectionColor.test.png").string());

  return 0;
}