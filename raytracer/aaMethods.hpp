#ifndef RAYTRACER_AAMETHODS_H_
#define RAYTRACER_AAMETHODS_H_

#include <random>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

namespace renderer {
namespace antialiasing {

using method = void (*)(int, int, int, double&, double&);

method
normal(
  [](int rpp, int subPixelX, int subPixelY, double& di, double& dj) -> void {
    di = (subPixelX + 0.5) / rpp;
    dj = (subPixelY + 0.5) / rpp;
  });

method
jittered(
  [](int rpp, int subPixelX, int subPixelY, double& di, double& dj) -> void {
    di = (subPixelX + distribution(generator)) / rpp;
    dj = (subPixelY + distribution(generator)) / rpp;
  });

method
random(
  [](int rpp, int subPixelX, int subPixelY, double& di, double& dj) -> void {
    di = distribution(generator);
    dj = distribution(generator);
  });
}
}

#endif