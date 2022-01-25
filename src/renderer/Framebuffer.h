#ifndef _FRAMEBUFFER_REECE_
#define _FRAMEBUFFER_REECE_

#include <vector>
#include <string>

#include "Vector3D.h"

using sivelab::Vector3D;

class Framebuffer
{
public:
  static const size_t DEFAULT_WIDTH = 100;
  static const size_t DEFAULT_HEIGHT = 100;

  Framebuffer(size_t width = DEFAULT_WIDTH, size_t height = DEFAULT_HEIGHT);

  size_t width();
  size_t height();

  void setPixelColor(size_t i, size_t j, const Vector3D &color);

  void exportAsPNG(const std::string &outputFileName);

  void clearColor(const Vector3D &color = Vector3D(1.0, 1.0, 1.0));

private:
  size_t m_width, m_height;
  std::vector<Vector3D> m_pixelArray;

  size_t index(size_t i, size_t j);
};

#endif