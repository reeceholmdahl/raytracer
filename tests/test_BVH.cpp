#include <iostream>
#include <vector>
#include <cassert>

#include <boost/filesystem.hpp>

#include "handleGraphicsArgs.h"

#include "Scene.hpp"
#include "Shape.hpp"
#include "Camera.hpp"
#include "HitStruct.hpp"
#include "Framebuffer.hpp"
#include "PerspectiveCamera.hpp"
#include "BVH.hpp"

namespace fs = boost::filesystem;

using renderer::Framebuffer;

int main(int argc, char *argv[])
{
    sivelab::GraphicsArgs args;
    args.process(argc, argv);

    // Used cmdline arguments
    const size_t nx(args.width), ny(args.height);
    // const size_t nx(500), ny(500);
    const fs::path outfile(args.outputFileName);
    // const fs::path indir(fs::path(args.inputFileName).parent_path());
    // const std::string fileName = "boxSphereTest.json";
    const fs::path infile(args.inputFileName);

    // Assert that the file exists
    // assert(fs::exists(infile));

    Scene scene(nx, ny);

    scene.parseJSONData(infile.string());

    auto bvh = BVH(scene.shapes());
    std::cout << "Made the BVH" << std::endl;

    std::vector<Framebuffer *> fbs(scene.cameras().size());
    for (int i(0); i < scene.cameras().size(); ++i)
    {
        fbs[i] = new Framebuffer(scene.pixelsX(), scene.pixelsY());
    }

    std::cout << "Cameras: " << scene.cameras().size() << std::endl
              << "Shapes: " << scene.shapes().size() << std::endl
              << "Lights: " << scene.lights().size() << std::endl;

    for (int c(0); c < scene.cameras().size(); ++c)
    {
        for (size_t i(0); i < nx; ++i)
        {
            std::cerr << i << std::endl;
            for (size_t j(0); j < ny; ++j)
            {
                auto cam = scene.cameras()[c];
                auto fb = fbs[c];
                auto ray = cam->generateRay(i, j);
                HitStruct hit(1, INFINITY, &scene.lights());
                // for (Shape *shape : scene.shapes())
                // {
                //     auto testHit = hit;
                //     if (shape->closestHit(ray, testHit))
                //     {
                //         hit = testHit;
                //     }
                // }

                auto didHit = bvh.head->closestHit(ray, hit);

                Vec3f color(scene.background());
                if (didHit && hit.shaderPtr)
                {
                    color = hit.shaderPtr->apply(hit);
                }

                fb->setPixelColor(i, j, color);
            }
        }
    }

    for (int i(0); i < fbs.size(); ++i)
    {
        auto fb = fbs[i];
        fb->exportAsPNG(outfile.string());
    }

    return 0;
}