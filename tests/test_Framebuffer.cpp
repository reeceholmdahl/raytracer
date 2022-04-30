#include <iostream>
#include <filesystem>

#include <boost/progress.hpp>
#include "handleGraphicsArgs.h"

#include "Vector3.hpp"
#include "Framebuffer.hpp"

using namespace renderer;

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  // Used cmdline arguments
  const size_t nx(args.width), ny(args.height);
  const fs::path outdir(fs::path(args.outputFileName).parent_path());

  boost::progress_timer ptimer;
  double startTime = ptimer.elapsed();

  // Create Framebuffers to hold the 2D data for our scenes
  Framebuffer fb1(12, 12), fb2(24, 36), fb3(43, 19), fb4(nx, ny), fb5(nx, ny), fb6(nx, ny), fb7(nx, ny);

  // Create a Framebuffer that we won't touch at all
  Framebuffer fb8(nx, ny);

  // Clear colors as red, green, then blue for the first 3 required tests
  fb1.clearColor(Vec3f(1.0, 0.0, 0.0));
  fb2.clearColor(Vec3f(0.0, 1.0, 0.0));
  fb3.clearColor(Vec3f(0.0, 0.0, 1.0));

  // Tests frameBuffer::clearColor by setting whole buffer to purple
  fb4.clearColor(Vec3f(1.0, 0.0, 1.0));

  // One of my random Framebuffer test
  double centerX = fb5.width() / 2.;
  double centerY = fb5.height() / 2.;
  for (auto i = 0; i < fb5.width(); ++i)
  {
    for (auto j = 0; j < fb5.height(); ++j)
    {
      double dx = abs(centerX - i);
      double dy = abs(centerY - j);
      double maxDistance = std::min(centerX, centerY);
      double distance = sqrt(dx * dx + dy * dy);
      double light = std::min(1.0, distance / maxDistance);
      fb5.setPixelColor(i, j, Vec3f(0.4 * (1.0 - light), 0.4 * (1.0 - light) * sin(0.06 * j + 1.2) + 0.5 * (1.0 - light), 1.0 - light));
    }
  }

  // One of my random Framebuffer test
  for (auto i = 0; i < fb6.width(); ++i)
  {
    for (auto j = 0; j < fb6.height(); ++j)
    {
      double dx = abs(centerX - i);
      double dy = abs(centerY - j);
      double maxDistance = std::min(centerX, centerY);
      double distance = sqrt(dx * dx + dy * dy);
      double light = std::min(1.0, distance / maxDistance);
      fb6.setPixelColor(i, j, Vec3f(1.0 - dx / centerX, 0.5 * (1.0 - light), 1.0 - dy / centerY));
    }
  }

  // One of my random Framebuffer test
  for (auto i = 0; i < fb7.width(); ++i)
  {
    for (auto j = 0; j < fb7.height(); ++j)
    {

      double ci = i - static_cast<double>(fb7.width()) / 2;
      double cj = j - static_cast<double>(fb7.height()) / 2;

      auto size = std::min(fb7.width(), fb7.height());

      double x = static_cast<double>(ci) / size;
      double y = static_cast<double>(cj) / size;

      double cx = x;
      double cy = y;

      double dCenter = sqrt(cx * cx + cy * cy);

      // fb7.setPixelColor(i, j, sivelab::Vector3D(dCenter < 0.25 ? 1 : 0, dCenter < 0.25 ? 1 : 0, dCenter < 0.25 ? 1 : 0));
      fb7.setPixelColor(i, j, Vec3f(dCenter < 0.25 ? dCenter : 1.0 - dCenter, dCenter < 0.25 ? dCenter : 1.0 - dCenter, dCenter < 0.25 ? 0.9 - 3.5 * dCenter * dCenter : 1.0 - dCenter));
    }
  }

  Framebuffer fb9(fb7);

  // When complete, output the files
  fb1.exportAsPNG((outdir / "test_Framebuffer1.test.png").string());
  fb2.exportAsPNG((outdir / "test_Framebuffer2.test.png").string());
  fb3.exportAsPNG((outdir / "test_Framebuffer3.test.png").string());
  fb4.exportAsPNG((outdir / "test_Framebuffer4.test.png").string());
  fb5.exportAsPNG((outdir / "test_Framebuffer5.test.png").string());
  fb6.exportAsPNG((outdir / "test_Framebuffer6.test.png").string());
  fb7.exportAsPNG((outdir / "test_Framebuffer7.test.png").string());
  fb8.exportAsPNG((outdir / "test_Framebuffer8.test.png").string());
  fb9.exportAsPNG((outdir / "test_Framebuffer9.test.png").string());

  double endTime = ptimer.elapsed();
  std::cout << "Rendering time: " << endTime - startTime << std::endl;
}