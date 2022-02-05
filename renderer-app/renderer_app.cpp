#include <iostream>
#include <vector>

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
Framebuffer renderer::renderScene(const size_t width, const size_t height, const SceneContainer &scene)
{

    return Framebuffer();
}

// exportAsPNG - app and gui (optional) : void
// use drawn Framebuffer(s) to export as png (if app export all cameras at once, if gui export currently viewing one)

// generateTexture - gui : GLuint&
// generate openGL texture from framebuffer

// drawFrame - gui : void
// draw full screen quad textured by framebuffer

// changeCamera - gui : void
// render scene using another camera and re-generateTexture and re-drawFrame

// handleInput - gui : void
// Passes boolean indicating activation of selected keys and develop respective functionality of handling input