#include "PerspectiveCamera.hpp"
#include <iostream>

const double PerspectiveCamera::DEFAULT_FOCAL_LENGTH = 1.0;

PerspectiveCamera::PerspectiveCamera(const Vec3d &position, const Vec3d &viewDir, const double focalLength, const double imagePlaneWidth, const double aspectRatio)
    : Camera(position, viewDir, imagePlaneWidth, aspectRatio), m_focalLength(focalLength)
{
}

Ray PerspectiveCamera::generateRay(const size_t i, const size_t j) const
{
    // Can be calculated on position change, image size change, or framebuffer change
    auto l = -m_imagePlaneWidth / 2;
    auto r = m_imagePlaneWidth / 2;
    auto b = -m_imagePlaneHeight / 2;
    auto t = m_imagePlaneHeight / 2;

    auto u = l + (r - l) * (i + 0.5) / m_pixelsX;
    auto v = b + (t - b) * (j + 0.5) / m_pixelsY;

    Vec3d origin, direction(u, v, -m_focalLength);
    direction.set(
        basis().u().dot(direction),
        basis().v().dot(direction),
        basis().w().dot(direction));

    // std::cout << direction << std::endl;

    // Ray ray(basis().toGlobal(origin), basis().toGlobal(direction));
    Ray ray(basis().toGlobal(origin), direction);
    // Ray ray(basis().toGlobal(origin), direction);

    return ray;
}