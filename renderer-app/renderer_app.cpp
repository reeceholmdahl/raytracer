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
// builds fields for camera, framebuffer, sets up environment

// initOpenGL - gui : void
// launches window, sets up scene ready to draw fullscreen quad

// buildScene - app and gui : SceneContainer
// parses scene file and sets up SceneContainer

// renderScene - app and gui : Framebuffer
// render scene using built SceneContainer and selected camera to draw Framebuffer

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