#include <iostream>
#include <cassert>
#include <filesystem>
#include <vector>

#include "RayTracer.hpp"
#include "Scene.hpp"

#include "handleGraphicsArgs.h"

using namespace renderer;
namespace fs = std::filesystem;

namespace renderer {
int main(int argc, char *argv[]) {
  size_t width, height, windowWidth, windowHeight;
  fs::path scenePath, outputPath;

  loadArguments(argc, argv, width, height, windowWidth, windowHeight, scenePath,
                outputPath);

  Scene scene(width, height);
  Framebuffer fb(width, height);

  init(outputPath);

  scene.parseJsonFile(scenePath.string());

  renderScene(scene, fb);

  exportAsPNG(outputPath, fb);

  return 0;
}

void loadArguments(int argc, char *argv[], size_t &width, size_t &height,
                   size_t &windowWidth, size_t &windowHeight,
                   fs::path &scenePath, fs::path &outputPath) {
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  width = args.width;
  height = args.height;
  scenePath = fs::path(args.inputFileName);
  outputPath = fs::path(args.outputFileName);
  windowWidth = args.windowWidth;
  windowHeight = args.windowHeight;

  std::cout << "Image w/h: " << width << " by " << height << " pixels"
            << std::endl
            << "Window w/h: " << windowWidth << " by " << windowHeight
            << " pixels" << std::endl
            << "Scene path: " << scenePath << std::endl
            << "Output path: " << outputPath << std::endl;
}

// init - app and gui : void
// builds fields for camera, framebuffer, sets up environment
void init(const fs::path &outputPath) {
  auto outdir(outputPath.parent_path());
  if (!fs::exists(outdir)) {
    std::cout << "Creating ouput directory: " << outdir.string() << std::endl;
    fs::create_directories(outdir);
  } else {
    std::cout << "Output directory exists" << std::endl;
  }
}

// initOpenGL - gui : void
// launches window, sets up scene ready to draw fullscreen quad

// renderScene - app and gui : Framebuffer
// render scene using built Scene and selected camera to draw Framebuffer
void renderScene(Scene &scene, Framebuffer &fb, const int camera) {
  // Camera index is in range
  assert(camera >= 0 && camera < scene.cameras.size());

  Camera *cam = scene.cameras[camera];

  for (size_t i(0); i < fb.width(); ++i) {
    for (size_t j(0); j < fb.height(); ++j) {
      auto ray = cam->generateRay(i, j);
      HitStruct hit(1, INFINITY, &scene.lights);
      for (Shape *shape : scene.shapes) {
        auto testHit = hit;
        if (shape->closestHit(ray, testHit)) {
          hit = testHit;
        }
      }

      Vec3f color(scene.bgColor);
      if (hit.t != INFINITY && hit.shaderPtr) {
        color = hit.shaderPtr->apply(hit);
      }

      fb.setPixelColor(i, j, color);
    }
  }
}

// exportAsPNG - app and gui (optional) : void
// use drawn Framebuffer(s) to export as png (if app export all cameras at once,
// if gui export currently viewing one)
void exportAsPNG(const fs::path &outputPath, const Framebuffer &fb) {
  // for (int i(0); i < fbs.size(); ++i)
  // {
  //     auto outdir(outputPath.parent_path());
  //     auto filename(outputPath.stem().string() + std::to_string(i + 1));
  //     auto ext(outputPath.extension().string());

  //     auto output((outdir / (filename + ext)).string());
  //     std::cout << output << std::endl;
  //     fbs[i].exportAsPNG(output);
  // }

  // auto outdir(outputPath.parent_path());
  //     auto filename(outputPath.stem().string());
  //     auto ext(outputPath.extension().string());

  fb.exportAsPNG(outputPath.string());
  std::cout << "File created at: " << outputPath << std::endl;
}
}