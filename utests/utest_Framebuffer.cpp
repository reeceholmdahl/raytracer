#include <iostream>

#include <boost/progress.hpp>

#include "handleGraphicsArgs.h"
#include "Vector3D.h"
#include "Framebuffer.h"

int main(int argc, char *argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  boost::progress_timer ptimer;
  int startTime = ptimer.elapsed();

  // Create Framebuffers to hold the 2D data for our scenes
  Framebuffer fb1(12, 12), fb2(24, 36), fb3(43, 19), fb4(args.width, args.height), fb5(args.width, args.height), fb6(args.width, args.height), fb7(args.width, args.height);

  // Create a Framebuffer that we won't touch at all
  Framebuffer fb8(args.width, args.height);

  // Clear colors as red, green, then blue for the first 3 required tests
  fb1.clearColor(sivelab::Vector3D(1.0, 0.0, 0.0));
  fb2.clearColor(sivelab::Vector3D(0.0, 1.0, 0.0));
  fb3.clearColor(sivelab::Vector3D(0.0, 0.0, 1.0));

  // Tests frameBuffer::clearColor by setting whole buffer to purple
  fb4.clearColor(sivelab::Vector3D(1.0, 0.0, 1.0));

  // One of my random Framebuffer test
  double centerX = fb5.width() / 2.;
  double centerY = fb5.height() / 2.;
  for (auto i = 0; i < fb5.width(); ++i) {
    for (auto j = 0; j < fb5.height(); ++j) {
      double dx = abs(centerX - i);
      double dy = abs(centerY - j);
      double maxDistance = std::min(centerX, centerY);
      double distance = sqrt(dx * dx + dy * dy);
      double light = std::min(1.0, distance / maxDistance);
      fb5.setPixelColor(i, j, sivelab::Vector3D(0.4 * (1.0 - light), 0.4 * (1.0 - light) * sin(0.06 * j + 1.2) + 0.5 * (1.0 - light), 1.0 - light));
    }
  }

  // One of my random Framebuffer test
  for (auto i = 0; i < fb6.width(); ++i) {
    for (auto j = 0; j < fb6.height(); ++j) {
      double dx = abs(centerX - i);
      double dy = abs(centerY - j);
      double maxDistance = std::min(centerX, centerY);
      double distance = sqrt(dx * dx + dy * dy);
      double light = std::min(1.0, distance / maxDistance);
      fb6.setPixelColor(i, j, sivelab::Vector3D(1.0 - dx / centerX, 0.5 * (1.0 - light), 1.0 - dy / centerY));
    }
  }

  // One of my random Framebuffer test
  for (auto i = 0; i < fb7.width(); ++i) {
    for (auto j = 0; j < fb7.height(); ++j) {

      double ci = i - static_cast<double>(fb7.width()) / 2;
      double cj = j - static_cast<double>(fb7.height()) / 2;

      auto size = std::min(fb7.width(), fb7.height());

      double x = static_cast<double>(ci) / size;
      double y = static_cast<double>(cj) / size;

      double cx = x;
      double cy = y;

      double dCenter = sqrt(cx * cx + cy * cy);

      // fb7.setPixelColor(i, j, sivelab::Vector3D(dCenter < 0.25 ? 1 : 0, dCenter < 0.25 ? 1 : 0, dCenter < 0.25 ? 1 : 0));
      fb7.setPixelColor(i, j, sivelab::Vector3D(dCenter < 0.25 ? dCenter : 1.0 - dCenter, dCenter < 0.25 ? dCenter : 1.0 - dCenter, dCenter < 0.25 ? 0.9 - 3.5 * dCenter * dCenter : 1.0 - dCenter));
    }
  }

  // When complete, output the file
  std::string oFilename;
  if (args.isSet("outputfile", oFilename)) {
    fb1.exportAsPNG(oFilename + "1.test.png");
    fb2.exportAsPNG(oFilename + "2.test.png");
    fb3.exportAsPNG(oFilename + "3.test.png");
    fb4.exportAsPNG(oFilename + "4.test.png");
    fb5.exportAsPNG(oFilename + "5.test.png");
    fb6.exportAsPNG(oFilename + "6.test.png");
    fb7.exportAsPNG(oFilename + "7.test.png");
    fb8.exportAsPNG(oFilename + "8.test.png");
  }

  int endTime = ptimer.elapsed();
  std::cout << "Rendering time: " << endTime - startTime << std::endl;
}