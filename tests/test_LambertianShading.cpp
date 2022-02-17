#include <iostream>

#include <boost/filesystem.hpp>

#include "renderer.hpp"
#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "Vector3.hpp"
#include "CoordinateSys.hpp"
#include "Framebuffer.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "PointLight.hpp"

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

  Triangle tri(Vec3d(0.25, 0, -2), Vec3d(0, 0.1, -2.1), Vec3d(-0.1, -0.1, -2));
  Sphere sph1(Vec3d(-0.15, -0.15, -2), 0.25);
  Sphere sph2(Vec3d(0.5, 0, -4.5), 0.33);

  PointLight light(Vec3d(1, 1, -1), Vec3f(1, 1, 1));

  Camera *cam;
  cam = new PerspectiveCamera();
  cam->set_pixels_x(nx);
  cam->set_pixels_y(ny);

  for (size_t i = 0; i < nx; ++i)
  {
    for (size_t j = 0; j < ny; ++j)
    {
      auto r(cam->generateRay(i, j));

      double t(0), t_hitTri(INFINITY), t_hitSph1(INFINITY), t_hitSph2(INFINITY);
      auto hitTri(tri.closestHit(r, 0, INFINITY, t_hitTri));
      auto hitSph1(sph1.closestHit(r, 0, t_hitTri, t_hitSph1));
      auto hitSph2(sph2.closestHit(r, 0, std::min(t_hitTri, t_hitSph1), t_hitSph2));

      Vec3f color;
      if (hitSph2)
      {
        color.set(0.15, 0.85, 0.1);
        t = t_hitSph2;

        auto hitPoint(r.point(t));
        auto hitToLight((light.position() - hitPoint).unitize());
        auto normal(sph2.normal(hitPoint));

        // lambertian shading
        color *= (light.intensity() * std::max(0.0, normal.dot(hitToLight)));
      }
      else if (hitSph1)
      {
        // hit sphere or sphere is in front of triangle
        color.set(0.05, 0.05, 0.85);
        t = t_hitSph1;

        auto hitPoint(r.point(t));
        auto hitToLight((light.position() - hitPoint).unitize());
        auto normal(sph1.normal(hitPoint));

        // lambertian shading
        color *= (light.intensity() * std::max(0.0, normal.dot(hitToLight)));

        // color.set(hitToLight[0] + 1, hitToLight[1] + 1, hitToLight[2] + 1);
        // color.set(hitToLight.dot(normal) + 1, hitToLight.dot(normal) + 1, hitToLight.dot(normal) + 1);
        // color = hitToLight;
        // color += Vec3f(1.0, 1.0, 1.0);

        // normal shading
        // color = normal;
        // color += Vec3f(1.0, 1.0, 1.0);
        // color /= 2;

        // std::cout << i << "x " << j << "y | l: " << hitToLight << " n: " << normal << std::endl;
      }
      else if (hitTri)
      {
        // hit triangle
        color.set(1, 1, 0);
        t = t_hitTri;

        auto hitPoint(r.point(t));
        auto hitToLight((hitPoint - light.position()).unitize());
        auto normal(tri.normal(hitPoint));

        color *= std::max(0.0, normal.dot(hitToLight));
      }
      else
      {
        // hit nothing
        color.set(0.1, 0.1, 0.1);
        t = -1;
      }

      fb.setPixelColor(i, j, color);
    }
  }

  fb.exportAsPNG((outdir / "test_LambertianShading.test.png").string());

  return 0;
}