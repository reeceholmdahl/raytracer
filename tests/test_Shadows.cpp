#include <iostream>
#include <vector>
#include <string>

#include <boost/filesystem.hpp>

#include "renderer.hpp"
#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "Vector3.hpp"
#include "CoordSys.hpp"
#include "Framebuffer.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "PointLight.hpp"
#include "SceneContainer.hpp"

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

    SceneContainer scene;

    scene.add(new Sphere(Vec3d(-0.6, 0, -4), 0.5));
    scene.add(new Sphere(Vec3d(0.6, 0, -3), 0.5));

    scene.add(new PointLight(Vec3d(1, 2, -1), Vec3f(1, 1, 1)));

    scene.add(new PerspectiveCamera());

    std::vector<Framebuffer> fbs;

    for (size_t i = 0; i < nx; ++i)
    {
        for (size_t j = 0; j < ny; ++j)
        {
            for (Camera *cam : scene.cameras())
            {
                auto ray(cam->generateRay(i, j));

                Vec3f color(0.1f, 0.1f, 0.1f);

                for ()
            }

            auto r(cam->generateRay(i, j));

            double t(0), t_hitTri(INFINITY), t_hitSph(INFINITY);
            auto hitTri(tri.closestHit(r, 0, INFINITY, t_hitTri));
            auto hitSph(sph.closestHit(r, 0, t_hitTri, t_hitSph));

            Vec3f color;
            if (hitSph)
            {
                // hit sphere or sphere is in front of triangle
                color.set(0.05, 0.05, 0.85);
                t = t_hitSph;

                auto hitPoint(r.point(t));
                auto hitToLight((light.position() - hitPoint).unitize());
                auto normal(sph.normal(hitPoint));

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