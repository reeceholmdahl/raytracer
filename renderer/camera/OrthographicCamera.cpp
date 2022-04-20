#include "OrthographicCamera.hpp"

// OrthographicCamera::OrthographicCamera()
//     : OrthographicCamera(Vec3d(), Vec3d())
// {
// }

OrthographicCamera::OrthographicCamera(const Vec3d &position, const Vec3d &viewDir, const double imagePlaneWidth, const double aspectRatio)
    : Camera(position, viewDir, imagePlaneWidth, aspectRatio)
{
}

Ray OrthographicCamera::generateRay(const size_t i, const size_t j) const
{
    // Can be calculated on position change, image size change, or framebuffer change
    auto l = -m_imagePlaneWidth / 2;
    auto r = m_imagePlaneWidth / 2;
    auto b = -m_imagePlaneHeight / 2;
    auto t = m_imagePlaneHeight / 2;

    auto u = l + (r - l) * (i + 0.5) / m_pixelsX;
    auto v = b + (t - b) * (j + 0.5) / m_pixelsY;

    Vec3d origin(u, v, 0);

    Ray ray(basis().toGlobal(origin), basis().toGlobal(Vec3d(0, 0, -1)));

    return ray;
}