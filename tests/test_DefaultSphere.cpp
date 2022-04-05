#include <iostream>

#include "boost/filesystem.hpp"

#include "renderer.hpp"
#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "OrthographicCamera.hpp"
#include "Vector3.hpp"
#include "CoordSys.hpp"
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

    Framebuffer fbPersp(nx, ny);
    Framebuffer fbOrtho(nx, ny);

    Sphere sph;

    Camera *persp = new PerspectiveCamera();
    Camera *ortho = new OrthographicCamera();

    persp->set_pixels_x(nx);
    persp->set_pixels_y(ny);
    ortho->set_pixels_x(nx);
    ortho->set_pixels_y(ny);

    for (size_t i(0); i < nx; ++i)
    {
        for (size_t j(0); j < ny; ++j)
        {
            auto orthoRay(ortho->generateRay(i, j));
            auto perspRay(persp->generateRay(i, j));

            auto hitOrtho = HitStruct();
            auto hitPersp = HitStruct();

            Vec3f colorPersp(0.1, 0.1, 0.1);
            Vec3f colorOrtho(0.1, 0.1, 0.1);
            if (sph.closestHit(perspRay, 1, INFINITY, hitPersp))
            {
                colorPersp = hitPersp.shaderPtr->apply(hitPersp);
            }

            if (sph.closestHit(orthoRay, 1, INFINITY, hitOrtho))
            {
                colorOrtho = hitOrtho.shaderPtr->apply(hitOrtho);
            }

            fbPersp.setPixelColor(i, j, colorPersp);
            fbOrtho.setPixelColor(i, j, colorOrtho);
        }
    }

    fbPersp.exportAsPNG((outdir / "test_DefaultSpherePerspective.test.png").string());
    fbOrtho.exportAsPNG((outdir / "test_DefaultSphereOrthographic.test.png").string());

    return 0;
}