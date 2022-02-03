#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "handleGraphicsArgs.h"

#include "renderer.hpp"
#include "Framebuffer.hpp"
#include "Vector3.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "CoordinateSys.hpp"

using namespace renderer;

Framebuffer renderCycle(int &count, int index, Camera *cam, Framebuffer (*fb)(size_t, size_t, Camera *), const size_t nx, const size_t ny);
Framebuffer sphereNormal(const size_t nx, const size_t ny, Camera *cam);

int main(int argc, char *argv[])
{
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    sivelab::GraphicsArgs args;
    args.process(argc, argv);

    // Used cmdline arguments
    const size_t nx(args.width), ny(args.height);

    int windowWidth(nx);
    int windowHeight(ny);
    int aspectRatio = nx / ny;

    GLFWwindow *window(glfwCreateWindow(windowWidth, windowHeight, "test_Window", NULL, NULL));

    if (!window)
    {
        std::cerr << "GLFW did not create the window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err(glewInit());
    if (err != GLEW_OK)
    {
        std::cerr << "glewInit failed, exiting." << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    int fb_w, fb_h;
    glfwGetFramebufferSize(window, &fb_w, &fb_h);
    glViewport(0, 0, fb_w, fb_h);

    Vec3d u, v, w;

    u.set(1, 0, 0);
    w.set(0, 0, 1);
    v = u.cross(w);

    CoordinateSys basis(Vec3d(0, 0, 0), u, v, -w);

    Camera *camera;
    camera = new PerspectiveCamera("persp", basis, 1.0, fb_w, fb_h, 1.0, 1.0 / aspectRatio);

    int renderCount(0);
    while (!glfwWindowShouldClose(window))
    {
        // Render code goes here
        std::cout << "renderCount " << renderCount << std::endl;
        Framebuffer fb(renderCycle(renderCount, 0, camera, sphereNormal, fb_w, fb_h));
        // Framebuffer fb(fb_w, fb_h);
        std::cout << "renderCount " << renderCount << std::endl;

        float *pixels = framebufferToGLPixelArray(fb);
        std::cout << "hello" << std::endl;
        // for (size_t i(0); i < 3 * fb_w * fb_h; ++i)
        // {
        //     std::cout << pixels[i] << " ";
        //     if (i % 3 == 2)
        //         std::cout << std::endl;
        // }

        GLuint texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float borderColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fb_w, fb_h, 0, GL_RGB, GL_FLOAT, pixels);

        //! I think this line is causing problems
        glBlitNamedFramebuffer(texture, 0, 0, 0, fb_w, fb_h, 0, 0, fb_w, fb_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);

        // Event polling
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        {
            std::cout << "Test";
        }
    }

    glfwTerminate();
    return 0;
}

Framebuffer renderCycle(int &count, const int index, Camera *cam, Framebuffer (*fb)(size_t, size_t, Camera *), const size_t nx, const size_t ny)
{
    if (count == index)
    {
        ++count;
        return fb(nx, ny, cam);
    }

    return Framebuffer();
}

Framebuffer sphereNormal(const size_t nx, const size_t ny, Camera *cam)
{
    Framebuffer fb(nx, ny);

    Sphere sph(Vec3d(0, 0, 2), 0.5);

    for (size_t i(0); i < nx; ++i)
    {
        for (size_t j(0); j < ny; ++j)
        {
            auto ray(cam->generateRay(i, j));

            double hit_T(0);
            auto hit(sph.closestHit(ray, 0, INFINITY, hit_T));

            Vec3f color(0.1, 0.1, 0.1);
            if (hit)
            {
                auto normal(sph.normal(ray.point(hit_T)));

                // normal shading
                color = normal;
                color += Vec3f(1.0, 1.0, 1.0);
                color /= 2;
            }

            fb.setPixelColor(i, j, color);
        }
    }

    return fb;
}