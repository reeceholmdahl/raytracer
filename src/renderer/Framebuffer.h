#pragma once

#include <vector>
#include <string>

#include "Vector3D.h"

class Framebuffer
{
public:
  static const int DEFAULT_WIDTH = 100;
  static const int DEFAULT_HEIGHT = 100;

  Framebuffer(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);

  int width();
  int height();

  void setPixelColor(int i, int j, const sivelab::Vector3D &color);

  void exportAsPNG(std::string outputFileName);

private:
  int m_width, m_height;
  std::vector<sivelab::Vector3D> m_pixelArray;

  int index(int i, int j);
};