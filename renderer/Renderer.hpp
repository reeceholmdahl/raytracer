#ifndef RENDERER_RENDERER_H_
#define RENDERER_RENDERER_H_

#include <filesystem>
#include <string>
#include <vector>

#include "Framebuffer.hpp"
#include "Scene.hpp"

namespace fs = std::filesystem;

namespace renderer {
class Renderer
{
public:
  Renderer() = delete;

  virtual void render(const Scene& scene) = 0;

  virtual const Framebuffer& framebuffer() const { return fb; }
  virtual size_t imageWidth() const { return m_imageWidth; }
  virtual size_t imageHeight() const { return m_imageHeight; }
  virtual size_t windowWidth() const { return m_windowWidth; }
  virtual size_t windowHeight() const { return m_windowHeight; }
  virtual double aspectRatio() const { return m_aspectRatio; }

private:
  size_t m_imageWidth, m_imageHeight, m_windowWidth, m_windowHeight;
  double m_aspectRatio;
  fs::path scenePath, outputPath;
  bool useShadows;
  int recursionDepth, rpp;
  Framebuffer fb;
};
}

#endif