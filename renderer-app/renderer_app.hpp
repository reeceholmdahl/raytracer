#ifndef _RENDERER_APP_REECE_
#define _RENDERER_APP_REECE_

#include <string>

#include <boost/filesystem.hpp>

#include "SceneContainer.hpp"

namespace fs = boost::filesystem;

namespace renderer
{
    void getArguments(int argc, char *argv[], size_t &width, size_t &height, size_t &windowWidth, size_t &windowHeight, fs::path &sceneFile, fs::path &outputPath);

    void init(const fs::path &outputPath);

    void initOpenGL(const size_t windowWidth, const size_t windowHeight, const std::string &title);

    SceneContainer buildScene(const fs::path &sceneFile);
}

#endif