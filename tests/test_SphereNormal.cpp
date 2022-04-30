#include <iostream>
#include <filesystem>

#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "Vector3.hpp"
#include "CoordSys.hpp"
#include "Framebuffer.hpp"
#include "Sphere.hpp"
#include "NormalShader.hpp"

#include "handleGraphicsArgs.h"

using namespace renderer;

namespace fs = std::filesystem;

int
main(int argc, char* argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  // Used cmdline arguments
  const size_t nx(args.width), ny(args.height);
  const fs::path outfile(args.outputFileName);

  Framebuffer fb(nx, ny);

  Sphere sph;
  sph.shaderPtr = new NormalShader();

  Camera* cam = new PerspectiveCamera();

  cam->setImagePixels(nx, ny);

  for (size_t i(0); i < nx; ++i) {
    for (size_t j(0); j < ny; ++j) {
      auto r(cam->generateRay(i, j));

      HitStruct hit;

      Vec3f color(0.1, 0.1, 0.1);
      if (sph.closestHit(r, hit)) {
        color = hit.shaderPtr->apply(hit);
      }

      fb.setPixelColor(i, j, color);
    }
  }

  fb.exportAsPNG(outfile.string());

  return 0;
}