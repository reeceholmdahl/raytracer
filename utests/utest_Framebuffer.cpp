#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>

#include <boost/progress.hpp>
#include <boost/date_time.hpp>

#include "png++/png.hpp"

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
  Framebuffer fb1(args.width, args.height), fb2(args.width, args.height), fb3(args.width, args.height);

  // Set all the framebuffer pixels to purple for fb1
  for (auto i = 0; i < fb1.width(); ++i) {
    for (auto j = 0; j < fb1.height(); ++j) {
      fb1.setPixelColor(i, j, sivelab::Vector3D(1.0, 0.0, 1.0));
    }
  }

  auto centerX = fb2.width() / 2;
  auto centerY = fb2.height() / 2;
  for (auto i = 0; i < fb2.width(); ++i) {
    for (auto j = 0; j < fb2.height(); ++j) {
      auto dx = abs(centerX - i);
      auto dy = abs(centerY - j);
      double maxDistance = sqrt(centerX * centerX + centerY * centerY);
      double distance = sqrt(dx * dx + dy * dy);
      double light = distance / maxDistance;
      fb2.setPixelColor(i, j, sivelab::Vector3D(1.0 - light, 1.0 - light, 1.0 - light));
    }
  }

  for (auto i = 0; i < fb3.width(); ++i) {
    for (auto j = 0; j < fb3.height(); ++j) {
      double dx = abs(centerX - i);
      double dy = abs(centerY - j);
      double maxDistance = sqrt(centerX * centerX + centerY * centerY);
      double distance = sqrt(dx * dx + dy * dy);
      double light = distance / maxDistance;
      fb3.setPixelColor(i, j, sivelab::Vector3D(dx / centerX, 1.0 - light, dy / centerY));
    }
  }

  // When complete, output the file
  std::string oFilename;
  if (args.isSet("outputfile", oFilename)) {
    fb1.exportAsPNG("1" + oFilename);
    fb2.exportAsPNG("2" + oFilename);
    fb3.exportAsPNG("3" + oFilename);
  }

  int endTime = ptimer.elapsed();
  std::cout << "Rendering time: " << endTime - startTime << std::endl;
}