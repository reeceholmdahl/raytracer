#ifndef _RENDERER_APP_REECE_
#define _RENDERER_APP_REECE_

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

#include "SceneContainer.hpp"
#include "Framebuffer.hpp"

namespace fs = boost::filesystem;

namespace renderer
{
    void getArguments(int argc, char *argv[], size_t &width, size_t &height, size_t &windowWidth, size_t &windowHeight, fs::path &sceneFile, fs::path &outputPath);

    void init(const fs::path &outputPath);

    void initOpenGL(const size_t windowWidth, const size_t windowHeight, const std::string &title);

    SceneContainer buildScene(const fs::path &sceneFile);

    Framebuffer renderScene(const size_t width, const size_t height, const SceneContainer &scene, const int camera = 0);

    void exportAsPNG(const fs::path &outputPath, const std::vector<Framebuffer> &fbs);

    void generateTexture(const Framebuffer &fb);

    void drawFrame();

    void changeCamera(const int camera);

    void handleInput(
        const bool rerenderScene,
        const bool openNewScene,
        const bool exportScene,
        const bool changeRenderSize,
        const bool prevCamera,
        const bool nextCamera);
}

#endif