#include <string>
#include <cmath>

#include "Framebuffer.hpp"
#include "Vector3.hpp"
#include "png++/png.hpp"

using namespace renderer;

Framebuffer::Framebuffer(size_t width, size_t height)
    : m_width(width), m_height(height), m_pixelArray(m_width * m_height)
{
  // clearColor(Vec3f(0.0, 0.0, 0.0));
}

Framebuffer::Framebuffer(const Framebuffer &f)
    : m_width(f.width()), m_height(f.height()), m_pixelArray(m_width * m_height)
{
  for (size_t i = 0; i < f.width(); ++i)
  {
    for (size_t j = 0; j < f.height(); ++j)
    {
      setPixelColor(i, j, f.m_pixelArray[index(i, j)]);
    }
  }
}

size_t Framebuffer::width() const
{
  return m_width;
}

size_t Framebuffer::height() const
{
  return m_height;
}

void Framebuffer::setPixelColor(size_t i, size_t j, const Vec3f &color)
{
  m_pixelArray[index(i, j)] = color;
}

void Framebuffer::exportAsPNG(const std::string &outputFileName) const
{
  png::image<png::rgb_pixel> imageData(m_width, m_height);

  for (size_t i = 0; i < width(); ++i)
  {
    for (size_t j = 0; j < height(); ++j)
    {
      Vec3f pixel(m_pixelArray[index(i, height() - j - 1)]);
      imageData[j][i] = png::rgb_pixel(pixel[0] * 255, pixel[1] * 255, pixel[2] * 255);
    }
  }

  imageData.write(outputFileName);
}

void Framebuffer::clearColor(const Vec3f &color)
{
  for (size_t i = 0; i < width(); ++i)
  {
    for (size_t j = 0; j < height(); ++j)
    {
      setPixelColor(i, j, color);
    }
  }
}

// size_t Framebuffer::index(size_t i, size_t j) const
// {
//   return i + j * m_width;
// }