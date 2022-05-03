#include <iostream>

#include "Framebuffer.hpp"
#include "Triangle.hpp"

#include "handleGraphicsArgs.h"

void
calcBarycentricCoords(const Triangle& tri,
                      const Vec3d& p,
                      double& alpha,
                      double& beta,
                      double& gamma)
{
  double facp = (tri.m_c[1] - tri.m_a[1]) * p[0] -
                (tri.m_c[0] - tri.m_a[0]) * p[1] + tri.m_c[0] * tri.m_a[1] -
                tri.m_c[1] * tri.m_a[0];

  double facb = (tri.m_c[1] - tri.m_a[1]) * tri.m_b[0] -
                (tri.m_c[0] - tri.m_a[0]) * tri.m_b[1] +
                tri.m_c[0] * tri.m_a[1] - tri.m_c[1] * tri.m_a[0];

  double fabp = (tri.m_b[1] - tri.m_a[1]) * p[0] -
                (tri.m_b[0] - tri.m_a[0]) * p[1] + tri.m_b[0] * tri.m_a[1] -
                tri.m_b[1] * tri.m_a[0];

  double fabc = (tri.m_b[1] - tri.m_a[1]) * tri.m_c[0] -
                (tri.m_b[0] - tri.m_a[0]) * tri.m_c[1] +
                tri.m_b[0] * tri.m_a[1] - tri.m_b[1] * tri.m_a[0];

  beta = facp / facb;
  gamma = fabp / fabc;
  alpha = 1 - beta - gamma;
}

int
main(int argc, char* argv[])
{
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  Vec3f bgColor(1, 0.25, 10);

  renderer::Framebuffer fb(args.width, args.height);
  fb.clearColor(bgColor);

  Triangle tri1(Vec3d(20, 40, 0), Vec3d(120, 80, 0), Vec3d(200, 200, 0)),
    tri2(Vec3d(400, 40, 0), Vec3d(470, 100, 0), Vec3d(425, 200, 0));

  Vec3f triColor(0.2, 1.0, 0.25);

  auto drawing(tri2);
  auto bbox(drawing.bbox());

  for (int y(bbox.minPt()[1]); y < (int)bbox.maxPt()[1]; ++y) {
    for (int x(bbox.minPt()[0]); x < (int)bbox.maxPt()[0]; ++x) {
      double alpha, beta, gamma;
      calcBarycentricCoords(drawing, Vec3d(x, y, 0), alpha, beta, gamma);
      if (beta > 0 && beta < 1 && gamma > 0 && gamma < 1 - beta) {
        fb.setPixelColor(x, y, triColor);
      }
    }
  }

  drawing = tri1;
  bbox = drawing.bbox();
  triColor = Vec3f(0.8, 0.4, 0.25);

  for (int y(bbox.minPt()[1]); y < (int)bbox.maxPt()[1]; ++y) {
    for (int x(bbox.minPt()[0]); x < (int)bbox.maxPt()[0]; ++x) {
      double alpha, beta, gamma;
      calcBarycentricCoords(drawing, Vec3d(x, y, 0), alpha, beta, gamma);
      if (beta > 0 && beta < 1 && gamma > 0 && gamma < 1 - beta) {
        fb.setPixelColor(x, y, triColor);
      }
    }
  }

  fb.exportAsPNG(args.outputFileName);

  return 0;
}