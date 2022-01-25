#include <string>
#include <cmath>

#include "Framebuffer.h"
#include "Vector3D.h"
#include "png++/png.hpp"

Framebuffer::Framebuffer(int width, int height)
  : m_width(width), m_height(height), m_pixelArray(m_width * m_height)
{
}

int Framebuffer::width()
{
  return m_width;
}

int Framebuffer::height()
{
  return m_height;
}

void Framebuffer::setPixelColor(int i, int j, const sivelab::Vector3D &color)
{
  m_pixelArray[index(i, j)] = color;
}

void Framebuffer::exportAsPNG(std::string outputFileName)
{
  png::image<png::rgb_pixel> imageData(m_width, m_height);

  for (unsigned int c = 0; c < m_width * m_height; ++c) {
    size_t i = c % m_width;
    size_t j = c / m_width;
    sivelab::Vector3D pixel(m_pixelArray[c]);
    imageData[j][i] = png::rgb_pixel(pixel[0] * 255, pixel[1] * 255, pixel[2] * 255);
  }

  imageData.write(outputFileName);
}

int Framebuffer::index(int i, int j)
{
  return i + j * m_width;
}