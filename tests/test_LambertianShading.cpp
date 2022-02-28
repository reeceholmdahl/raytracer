#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>

#include "renderer.hpp"
#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "Vector3.hpp"
#include "CoordinateSys.hpp"
#include "Framebuffer.hpp"
#include "Shape.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "PointLight.hpp"
#include "LambertShader.hpp"

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

  std::vector<Shape *> shapes;
  std::vector<Light *> lights;

  shapes.push_back(new Triangle(Vec3d(0.25, 0, -2), Vec3d(0, 0.1, -2.1), Vec3d(-0.1, -0.1, -2)));
  shapes.push_back(new Sphere(Vec3d(-0.15, -0.15, -2), 0.25));
  shapes.push_back(new Sphere(Vec3d(0.5, 0, -4.5), 0.33));

  lights.push_back(new PointLight(Vec3d(1, 1, -1), Vec3f(1, 1, 1)));

  Camera *cam;
  cam = new PerspectiveCamera();
  cam->set_pixels_x(nx);
  cam->set_pixels_y(ny);

  for (size_t i = 0; i < nx; ++i)
  {
    for (size_t j = 0; j < ny; ++j)
    {
      auto r(cam->generateRay(i, j));

      Shader *shader = new LambertShader(Vec3f(0.15, 0.15, 0.15), Vec3f(0, 0, 1));
      HitStruct hit;
      hit.t = INFINITY;
      for (Shape *shape : shapes)
      {
        shape->shaderPtr = shader;

        auto testHit = HitStruct();
        testHit.lights = &lights;
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

      // auto hit = HitStruct();

      // auto hitTri(tri.closestHit(r, 0, INFINITY, hit));
      // auto hitSph1(sph1.closestHit(r, 0, hit.t, hit));
      // auto hitSph2(sph2.closestHit(r, 0, hit.t, hit));

      // Vec3f color;
      // if (hitSph2)
      // {
      //   color.set(0.15, 0.85, 0.1);

      //   auto hitToLight((light.position() - hit.hitPoint()).unitize());
      //   auto normal(sph2.normal(hit.hitPoint()));

      //   // lambertian shading
      //   color *= (light.intensity() * std::max(0.0, normal.dot(hitToLight)));
      // }
      // else if (hitSph1)
      // {
      //   // hit sphere or sphere is in front of triangle
      //   color.set(0.05, 0.05, 0.85);

      //   auto hitToLight((light.position() - hit.hitPoint()).unitize());
      //   auto normal(sph1.normal(hit.hitPoint()));

      //   // lambertian shading
      //   color *= (light.intensity() * std::max(0.0, normal.dot(hitToLight)));

      //   // color.set(hitToLight[0] + 1, hitToLight[1] + 1, hitToLight[2] + 1);
      //   // color.set(hitToLight.dot(normal) + 1, hitToLight.dot(normal) + 1, hitToLight.dot(normal) + 1);
      //   // color = hitToLight;
      //   // color += Vec3f(1.0, 1.0, 1.0);

      //   // normal shading
      //   // color = normal;
      //   // color += Vec3f(1.0, 1.0, 1.0);
      //   // color /= 2;

      //   // std::cout << i << "x " << j << "y | l: " << hitToLight << " n: " << normal << std::endl;
      // }
      // else if (hitTri)
      // {
      //   // hit triangle
      //   color.set(1, 1, 0);

      //   auto hitToLight((hit.hitPoint() - light.position()).unitize());
      //   auto normal(tri.normal(hit.hitPoint()));

      //   color *= std::max(0.0, normal.dot(hitToLight));
      // }
      // else
      // {
      //   // hit nothing
      //   color.set(0.1, 0.1, 0.1);
      // }

      fb.setPixelColor(i, j, color);
    }
  }

  fb.exportAsPNG((outdir / "test_LambertianShading.test.png").string());

  return 0;
}