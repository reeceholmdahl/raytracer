#include <iostream>
#include <vector>
#include <cassert>

#include <boost/filesystem.hpp>

#include "renderer_app.hpp"
#include "renderer.hpp"
#include "SceneContainer.hpp"

#include "handleGraphicsArgs.h"

using namespace renderer;
namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
    SceneContainer scene;
    Framebuffer fb;
    size_t width, height, windowWidth, windowHeight;
    fs::path sceneFile, outputPath;

    getArguments(argc, argv, width, height, windowWidth, windowHeight, sceneFile, outputPath);

    std::cout << "w/h: " << width << " " << height << std::endl;
    std::cout << "window w/h: " << windowWidth << " " << windowHeight << std::endl;
    std::cout << "paths: " << sceneFile << " " << outputPath << std::endl;

    init(outputPath);

    return 0;
}

void renderer::getArguments(int argc, char *argv[], size_t &width, size_t &height, size_t &windowWidth, size_t &windowHeight, fs::path &sceneFile, fs::path &outputPath)
{
    sivelab::GraphicsArgs args;
    args.process(argc, argv);

    width = args.width;
    height = args.height;
    sceneFile = fs::path(args.inputFileName);
    outputPath = fs::path(args.outputFileName);
    windowWidth = args.windowWidth;
    windowHeight = args.windowHeight;
}

// init - app and gui : void
// builds fields for camera, framebuffer, sets up environment
void renderer::init(const fs::path &outputPath)
{
    auto outdir(outputPath.parent_path());
    if (!fs::exists(outdir))
    {
        std::cout << "Creating directory " << outdir.string() << std::endl;
        fs::create_directories(outdir);
    }
    else
    {
        std::cout << "Directory exists" << std::endl;
    }
}

// initOpenGL - gui : void
// launches window, sets up scene ready to draw fullscreen quad

// buildScene - app and gui : SceneContainer
// parses scene file and sets up SceneContainer
SceneContainer renderer::buildScene(const fs::path &sceneFile)
{
    return SceneContainer();
}

// renderScene - app and gui : Framebuffer
// render scene using built SceneContainer and selected camera to draw Framebuffer
Framebuffer renderer::renderScene(const size_t width, const size_t height, const SceneContainer &scene, const int camera)
{
    // Camera index is in range
    assert(camera >= 0 && camera < scene.cameras().size());

    Framebuffer fb(width, height);
    Camera *cam = scene.cameras()[camera];

    for (size_t i(0); i < width; ++i)
    {
        for (size_t j(0); j < height; ++j)
        {
            auto ray(cam->generateRay(i, j));

            Shape *hitShape;
            double hit_T(INFINITY);
            for (Shape *shape : scene.shapes())
            {
                double t;
                auto hit(shape->closestHit(ray, 0.0, INFINITY, t));

                if (hit && t < hit_T)
                {
                    hit_T = t;
                    hitShape = shape;
                }
            }

            Vec3f color(0.1f, 0.1f, 0.1f);
            if (hitShape)
            {
                color.set(1.0f, 1.0f, 0.0f);
            }

            fb.setPixelColor(i, j, color);
        }
    }

    return fb;
}

// exportAsPNG - app and gui (optional) : void
// use drawn Framebuffer(s) to export as png (if app export all cameras at once, if gui export currently viewing one)
void renderer::exportAsPNG(const fs::path &outputPath, const std::vector<Framebuffer> &fbs)
{
    for (int i(0); i < fbs.size(); ++i)
    {
        auto outdir(outputPath.parent_path());
        auto filename(outputPath.stem().string() + std::to_string(i + 1));
        auto ext(outputPath.extension().string());

        auto output((outdir / (filename + ext)).string());
        std::cout << output << std::endl;
        fbs[i].exportAsPNG(output);
    }
}
