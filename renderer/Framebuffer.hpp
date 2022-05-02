#ifndef RENDERER_FRAMEBUFFER_H_
#define RENDERER_FRAMEBUFFER_H_

#include <vector>
#include <string>

#include "Constants.h"
#include "Vector3.hpp"

namespace renderer {

class Framebuffer
{
public:
  Framebuffer(const size_t width = constants::DEFAULT_WIDTH,
              const size_t height = constants::DEFAULT_HEIGHT);
  Framebuffer(const Framebuffer& f);

  size_t width() const;
  size_t height() const;

  void setPixelColor(const size_t i, const size_t j, const Vec3f& color);

  void exportAsPNG(const std::string& outputFileName) const;

  void clearColor(const Vec3f& color = Vec3f(0.0f, 0.0f, 0.0f));

private:
  size_t m_width, m_height;
  std::vector<Vec3f> m_pixelArray;

  size_t index(const size_t i, const size_t j) const { return i + j * m_width; }

protected:
  friend void framebufferToGLPixelArray(const Framebuffer& fb, float* pixels);
};

void framebufferToGLPixelArray(const Framebuffer& fb, float* pixels);
}

#endif