#include <iostream>

#include "boost/filesystem.hpp"

#include "renderer.hpp"
#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "OrthographicCamera.hpp"
#include "Vector3.hpp"
#include "CoordinateSys.hpp"
#include "Framebuffer.hpp"
#include "Triangle.hpp"

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

    Framebuffer fbPersp(nx, ny);
    Framebuffer fbOrtho(nx, ny);

    Triangle tri(Vec3d(0, 0.5, -2.5), Vec3d(-0.25, -0.25, -2.5), Vec3d(0.25, -0.25, -2.5));

    Camera *persp = new PerspectiveCamera("persp", CoordinateSys::GLOBAL, 1.0, nx, ny, 1.0, 1.0 * ny / nx);
    Camera *ortho = new OrthographicCamera("ortho", CoordinateSys::GLOBAL, nx, ny, 1.0, 1.0 * ny / nx);

    for (size_t i(0); i < nx; ++i)
    {
        for (size_t j(0); j < ny; ++j)
        {
            auto orthoRay(ortho->generateRay(i, j));
            auto perspRay(persp->generateRay(i, j));

            double hit_T;
            auto hitPersp(tri.closestHit(perspRay, 1, INFINITY, hit_T));
            auto hitOrtho(tri.closestHit(orthoRay, 1, INFINITY, hit_T));

            Vec3f colorPersp(0.1, 0.1, 0.1);
            Vec3f colorOrtho(0.1, 0.1, 0.1);
            if (hitPersp)
            {
                colorPersp.set(1, 1, 0);
            }

            if (hitOrtho)
            {
                colorOrtho.set(1, 1, 0);
            }

            fbPersp.setPixelColor(i, j, colorPersp);
            fbOrtho.setPixelColor(i, j, colorOrtho);
        }
    }

    fbPersp.exportAsPNG((outdir / "test_RayTraceTrianglePerspective.test.png").string());
    fbOrtho.exportAsPNG((outdir / "test_RayTraceTriangleOrthographic.test.png").string());

    return 0;
}