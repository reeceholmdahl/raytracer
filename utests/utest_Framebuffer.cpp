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
  Framebuffer fb1(args.width, args.height), fb2(args.width, args.height), fb3(args.width, args.height), fb4(args.width, args.height);

  // Set all the framebuffer pixels to purple for fb1
  for (auto i = 0; i < fb1.width(); ++i) {
    for (auto j = 0; j < fb1.height(); ++j) {
      // fb1.setPixelColor(i, j, sivelab::Vector3D(1.0, 0.0, 1.0));
      fb1.clearColor(sivelab::Vector3D(1.0, 0.0, 1.0));
    }
  }

  double centerX = fb2.width() / 2.;
  double centerY = fb2.height() / 2.;
  for (auto i = 0; i < fb2.width(); ++i) {
    for (auto j = 0; j < fb2.height(); ++j) {
      double dx = abs(centerX - i);
      double dy = abs(centerY - j);
      double maxDistance = std::min(centerX, centerY);
      double distance = sqrt(dx * dx + dy * dy);
      double light = std::min(1.0, distance / maxDistance);
      fb2.setPixelColor(i, j, sivelab::Vector3D(0.4 * (1.0 - light), 0.4 * (1.0 - light) * sin(0.06 * j + 1.2) + 0.5 * (1.0 - light), 1.0 - light));
    }
  }

  for (auto i = 0; i < fb3.width(); ++i) {
    for (auto j = 0; j < fb3.height(); ++j) {
      double dx = abs(centerX - i);
      double dy = abs(centerY - j);
      double maxDistance = std::min(centerX, centerY);
      double distance = sqrt(dx * dx + dy * dy);
      double light = std::min(1.0, distance / maxDistance);
      fb3.setPixelColor(i, j, sivelab::Vector3D(1.0 - dx / centerX, 0.5 * (1.0 - light), 1.0 - dy / centerY));
    }
  }

  for (auto i = 0; i < fb4.width(); ++i) {
    for (auto j = 0; j < fb4.height(); ++j) {

      double ci = i - static_cast<double>(fb4.width()) / 2;
      double cj = j - static_cast<double>(fb4.height()) / 2;

      auto size = std::min(fb4.width(), fb4.height());

      double x = static_cast<double>(ci) / size;
      double y = static_cast<double>(cj) / size;

      double cx = x;
      double cy = y;

      double dCenter = sqrt(cx * cx + cy * cy);

      // fb4.setPixelColor(i, j, sivelab::Vector3D(dCenter < 0.25 ? 1 : 0, dCenter < 0.25 ? 1 : 0, dCenter < 0.25 ? 1 : 0));
      fb4.setPixelColor(i, j, sivelab::Vector3D(dCenter < 0.25 ? dCenter : 1.0 - dCenter, dCenter < 0.25 ? dCenter : 1.0 - dCenter, dCenter < 0.25 ? 0.9 - 3.5 * dCenter * dCenter : 1.0 - dCenter));
    }
  }

  // When complete, output the file
  std::string oFilename;
  if (args.isSet("outputfile", oFilename)) {
    fb1.exportAsPNG(oFilename + "1.png");
    fb2.exportAsPNG(oFilename + "2.png");
    fb3.exportAsPNG(oFilename + "3.png");
    fb4.exportAsPNG(oFilename + "4.png");
  }

  int endTime = ptimer.elapsed();
  std::cout << "Rendering time: " << endTime - startTime << std::endl;
}