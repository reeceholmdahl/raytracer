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

GLFWwindow *window;
GLuint texture;
Camera *camera;
size_t nx, ny;
float *pixels;

Framebuffer sphereNormal(const size_t nx, const size_t ny, Camera *cam);

void draw()
{
    // Render code goes here
    std::cout << "before render" << std::endl;
    // Framebuffer fb(sphereNormal(nx, ny, camera));
    Framebuffer fb(nx, ny);
    fb.clearColor(Vec3f(0.5, 0.5, 0));
    std::cout << "after render" << std::endl;

    framebufferToGLPixelArray(fb, pixels);
    std::cout << "after pixel conversion" << std::endl;

    // Debug print all pixels
    // for (size_t i(0); i < 3 * nx * ny; ++i)
    // {
    //     std::cout << pixels[i] << " ";
    //     if (i % 3 == 2)
    //         std::cout << std::endl;
    // }

    glLoadIdentity(); // Load identity matrix? Does this need to be here?

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nx, ny, 0, GL_RGB, GL_FLOAT, pixels);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2d(0.0, 0.0);
    glVertex2d(-1.0, -1.0);
    glTexCoord2d(1.0, 0.0);
    glVertex2d(1.0, -1.0);
    glTexCoord2d(1.0, 1.0);
    glVertex2d(1.0, 1.0);
    glTexCoord2d(0.0, 1.0);
    glVertex2d(-1.0, 1.0);
    glEnd();

    glfwSwapBuffers(window);

    glBindTexture(GL_TEXTURE_2D, 0);
}

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
    nx = args.width;
    ny = args.height;

    pixels = new float[3 * nx * ny];

    int windowWidth(nx);
    int windowHeight(ny);
    int aspectRatio = nx / ny;

    window = glfwCreateWindow(windowWidth, windowHeight, "test_Window", NULL, NULL);

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

    //Create orthographic view
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 0, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();

    Vec3d u, v, w;

    u.set(1, 0, 0);
    w.set(0, 0, 1);
    v = u.cross(w);

    CoordinateSys basis(Vec3d(0, 0, 0), u, v, w);

    camera = new PerspectiveCamera("persp", basis, 1.0, fb_w, fb_h, 1.0, 1.0 / aspectRatio);

    // Generate texture object
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glGenTextures(1, &texture);

    // Move to draw() ?
    glBindTexture(GL_TEXTURE_2D, texture);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // float borderColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // // Generate framebuffer object
    // GLuint fboId;
    // glGenFramebuffers(1, &fboId);
    // glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    // // Attach the texture to FBO color attachment point
    // glFramebufferTexture2D(GL_FRAMEBUFFER,       // 1. fbo target: GL_FRAMEBUFFER
    //                        GL_COLOR_ATTACHMENT0, // 2. attachment point
    //                        GL_TEXTURE_2D,        // 3. tex target: GL_TEXTURE_2D
    //                        texture,              // 4. tex ID
    //                        0);                   // 5. mipmap level: 0(base)

    // // Switch back to GLFW framebuffer
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // // set rendering destination to FBO
    // glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    // // clear buffers
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // // draw a scene to a texture directly

    // // unbind FBO
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //
    // glBindTexture(GL_TEXTURE_2D, texture);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    draw();

    while (!glfwWindowShouldClose(window))
    {
        // Event polling
        glfwWaitEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            std::cout << "Reload Render" << std::endl;
        }
    }

    glfwTerminate();
    return 0;
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