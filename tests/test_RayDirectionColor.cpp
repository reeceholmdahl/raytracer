#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>

#include "renderer.hpp"
#include "Vector3.hpp"
#include "CoordSys.hpp"
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
  // const size_t nx(args.width), ny(args.height);
  const size_t nx(350), ny(250);
  const fs::path outdir(args.outputDirectory);

  if (!fs::exists(outdir))
  {
    std::cout << "Creating directory " << outdir.string() << std::endl;
    fs::create_directories(outdir);
  }

  Framebuffer fb(nx, ny);

  std::vector<Camera *> cams(7);
  cams[0] = new PerspectiveCamera("1", CoordSys(), 1.0);
  cams[1] = new PerspectiveCamera("2", CoordSys(Vec3d(), Vec3d(0, 1, 0), Vec3d(0, 0, 1)), 1.0);
  cams[2] = new PerspectiveCamera("3", CoordSys(Vec3d(), Vec3d(0, 1, 0), Vec3d(1, 0, 0)), 1.0);
  cams[3] = new PerspectiveCamera("4", CoordSys(Vec3d(), Vec3d(0, 1, 0), Vec3d(-1, 0, 0)), 1.0);
  cams[4] = new PerspectiveCamera("5", CoordSys(Vec3d(-19, 12, 3), Vec3d(0, 0, -1), Vec3d(0, 1, 0)), 0.15);
  cams[5] = new PerspectiveCamera("6", CoordSys(Vec3d(-19, 12, 3), Vec3d(0, 0, 1), Vec3d(0, -1, 0)), 0.15);
  cams[6] = new PerspectiveCamera("7", CoordSys(Vec3d(), Vec3d(0, 1, 0), Vec3d(0, 0, -1)), 0.05);

  for (int c(0); c < 7; ++c)
  {
    std::cout << c << std::endl;

    cams[c]->set_pixels_y(ny);
    cams[c]->set_pixels_x(nx);

    for (size_t i = 0; i < nx; ++i)
    {
      for (size_t j = 0; j < ny; ++j)
      {

        auto r = cams[c]->generateRay(i, j);
        Vec3f color((Vec3f(1, 1, 1) + r.direction().unitize()) / 2);
        fb.setPixelColor(i, j, color);
      }
    }

    fb.exportAsPNG((outdir / ("test_RayDirectionColor" + std::to_string(c + 1) + ".test.png")).string());
  }

  return 0;
}