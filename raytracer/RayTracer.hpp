#ifndef RAYTRACER_RAYTRACER_H_
#define RAYTRACER_RAYTRACER_H_

#include <filesystem>
#include <string>
#include <vector>

#include "Framebuffer.hpp"
#include "Scene.hpp"
#include "aaMethods.hpp"

namespace fs = std::filesystem;

namespace renderer {
void
loadArguments(int argc,
              char* argv[],
              size_t& width,
              size_t& height,
              size_t& windowWidth,
              size_t& windowHeight,
              fs::path& sceneFile,
              fs::path& outputPath,
              bool& useBVH,
              bool& useShadows,
              int& recursionDepth,
              int& rpp);

void
init(const fs::path& outputPath);

void
initOpenGL(const size_t windowWidth,
           const size_t windowHeight,
           const std::string& title);

void
renderScene(Scene& scene,
            Framebuffer& fb,
            const int rpp = 1,
            antialiasing::method aaMethod = antialiasing::normal,
            const int camera = 0);

void
exportAsPNG(const fs::path& outputPath, const Framebuffer& fb);

void
generateTexture(const Framebuffer& fb);

void
drawFrame();

void
changeCamera(const int camera);

void
handleInput(const bool rerenderScene,
            const bool openNewScene,
            const bool exportScene,
            const bool changeRenderSize,
            const bool prevCamera,
            const bool nextCamera);
}

#endif