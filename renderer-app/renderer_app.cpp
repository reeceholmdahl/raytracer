#include <iostream>

#include <boost/filesystem.hpp>

#include "renderer_app.hpp"
#include "renderer.hpp"

#include "handleGraphicsArgs.h"

using namespace renderer;
namespace fs = boost::filesystem;

sivelab::GraphicsArgs args;

int main(int argc, char *argv[])
{
    // First line of main
    args.process(argc, argv);

    size_t width, height;
    fs::path sceneFile, outputPath;

    getArguments(width, height, sceneFile, outputPath);

    std::cout << "w/h: " << width << " " << height << std::endl;
    std::cout << "paths: " << sceneFile << " " << outputPath << std::endl;
    return 0;
}

void renderer::getArguments(size_t &width, size_t &height, fs::path &sceneFile, fs::path &outputPath)
{
    width = args.width;
    height = args.height;
    sceneFile = fs::path(args.inputFileName);
    outputPath = fs::path(args.outputFileName);
}

void renderer::getArguments(size_t &width, size_t &height, size_t &windowWidth, size_t &windowHeight, fs::path &sceneFile, fs::path &outputPath)
{
    getArguments(width, height, sceneFile, outputPath);
    windowWidth = args.windowWidth;
    windowHeight = args.windowWidth;
}

// init - app and gui : void
// initOpenGL - gui : void

// buildScene - app and gui : SceneContainer
// renderScene - app and gui : Framebuffer

// exportAsPNG - app and gui (optional) : void
// generateTexture - gui : GLuint&
// drawFrame - gui : void
// changeCamera - gui : void