#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>

#include "renderer.hpp"
#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "Vector3.hpp"
#include "CoordSys.hpp"
#include "Framebuffer.hpp"
#include "Shape.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "PointLight.hpp"
#include "BlinnPhongShader.hpp"

#include "handleGraphicsArgs.h"

using namespace renderer;

namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  // Used cmdline arguments
  const size_t nx(args.width), ny(args.height);
  const fs::path outfile(args.outputFileName);

  Framebuffer fb(nx, ny);

  std::vector<Shape *> shapes;
  std::vector<Light *> lights;

  shapes.push_back(new Triangle(Vec3d(0.25, 0, -2), Vec3d(0, 0.1, -2.1), Vec3d(-0.1, -0.1, -2)));
  shapes.push_back(new Sphere(Vec3d(-0.15, -0.15, -2), 0.25));
  shapes.push_back(new Sphere(Vec3d(0.5, 0, -4.5), 0.33));

  lights.push_back(new PointLight(Vec3d(1, 1, -3), Vec3f(1, 1, 1)));
  lights.push_back(new PointLight(Vec3d(-1, 1, -1), Vec3f(1, 1, 1)));

  Camera *cam;
  cam = new PerspectiveCamera();
  cam->setImagePixels(nx, ny);

  Shader *shader = new BlinnPhongShader(Vec3f(0.3, 0.3, 0.3), Vec3f(0.7645, 0.6446, 0), Vec3f(0.85, 1, 0) / 2, 200);
  for (size_t i = 0; i < nx; ++i)
  {
    for (size_t j = 0; j < ny; ++j)
    {
      auto r(cam->generateRay(i, j));

      HitStruct hit;
      hit.t = INFINITY;
      for (Shape *shape : shapes)
      {
        shape->setShader(shader);

        auto testHit = HitStruct(lights);
        if (shape->closestHit(r, 1, hit.t, testHit))
        {
          hit = testHit;
        }
      }

      Vec3f color(0.1, 0.1, 0.1);
      if (hit.t != INFINITY && hit.shaderPtr)
      {
        color = hit.shaderPtr->apply(hit);
      }

      fb.setPixelColor(i, j, color);
    }
  }

  fb.exportAsPNG(outfile.string());

  return 0;
}