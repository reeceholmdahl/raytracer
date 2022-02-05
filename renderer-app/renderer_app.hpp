#ifndef _RENDERER_APP_REECE_
#define _RENDERER_APP_REECE_

#include <string>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace renderer
{
    void getArguments(size_t &width, size_t &height, fs::path &sceneFile, fs::path &outputPath);
    void getArguments(size_t &width, size_t &height, size_t &windowWidth, size_t &windowHeight, fs::path &sceneFile, fs::path &outputPath);
}

#endif