#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "CoordSys.hpp"
#include "Framebuffer.hpp"
#include "Vector3.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"

#include "handleGraphicsArgs.h"

using namespace renderer;

void createImage(GLuint& textureId, float* pixels, const size_t nx,
                 const size_t ny, Camera* cam,
                 Framebuffer (*gen_fb)(size_t, size_t, Camera*));

Framebuffer sphereNormal(const size_t nx, const size_t ny, Camera* cam);

int
main(int argc, char* argv[])
{
  // Process cmdline args
  sivelab::GraphicsArgs args;
  args.process(argc, argv);

  size_t nx(args.width), ny(args.height);

  // Initialize the library
  if (!glfwInit()) {
    return -1;
  }

  GLFWwindow* window;
  Camera* camera;
  Framebuffer fb(nx, ny);
  float* pixels = new float[3 * nx * ny];
  float* pixelsOut = new float[3 * nx * ny];
  GLuint textureId;

  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(nx, ny, "Hello World", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  GLenum err(glewInit());
  if (err != GLEW_OK) {
    std::cerr << "glewInit failed, exiting." << std::endl;
    return -1;
  }

  float vertices[] = {
    1.0, 1.0, // top right corner
    0.0, 1.0, // top left corner
    0.0, 0.0, // bottom left corner
    1.0, 0.0  // bottom right corner
  };

  float texcoords[] = {
    1.0, 1.0, // top right corner
    0.0, 1.0, // top left corner
    0.0, 0.0, // bottom left corner
    1.0, 0.0  // bottom right corner
  };

  camera = new PerspectiveCamera();

  glViewport(0, 0, nx, ny); // specifies the part of the window to which OpenGL
                            // will draw (in pixels), convert from normalised to
                            // pixels
  glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of
                               // the camera that views the objects in the world
                               // coordinate frame. Here you typically set the
                               // zoom factor, aspect ratio and the near and far
                               // clipping planes
  glLoadIdentity(); // replace the current matrix with the identity matrix and
                    // starts us a fresh because matrix transforms such as
                    // glOrpho and glRotate cumulate, basically puts us at (0,
                    // 0, 0)
  glOrtho(0., 1., 0., 1., 0., 1.); // essentially set coordinate system
  glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines
                              // how your objects are transformed (meaning
                              // translation, rotation and scaling) in your
                              // world
  glLoadIdentity();           // same as above comment

  glGenTextures(1, &textureId);

  // Render code goes here
  // std::cout << "before render" << std::endl;
  // fb = sphereNormal(nx, ny, camera);
  // // fb.clearColor(Vec3f(0.5, 0.5, 0));
  // std::cout << "after render" << std::endl;

  // framebufferToGLPixelArray(fb, pixels);
  // std::cout << "after pixel conversion" << std::endl;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, nx, ny, 0, GL_RGB, GL_FLOAT,
  // pixels);

  // glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, pixelsOut);
  // Debug print all pixels
  // for (size_t i(0); i < 3 * nx * ny; ++i)
  // {
  //     std::cout << pixelsOut[i] << " ";
  //     if (i % 3 == 2)
  //         std::cout << std::endl;
  // }

  glBindTexture(GL_TEXTURE_2D, 0);

  createImage(textureId, pixels, nx, ny, camera, sphereNormal);

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Render OpenGL here
    glBindTexture(GL_TEXTURE_2D, textureId);
    glEnableClientState(GL_VERTEX_ARRAY_EXT); // tell OpenGL that you're using a
                                              // vertex array for fixed-function
                                              // attribute
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); // tell OpenGL that you're
                                                 // using a vertex array for
                                                 // fixed-function attribute
    glVertexPointer(2, GL_FLOAT, 0,
                    vertices); // point to the vertices to be used
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_QUADS, 0, 4);          // draw the vertixes
    glDisableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're finished
                                           // using the vertex arrayattribute
    glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);

    glBindTexture(GL_TEXTURE_2D, 0);

    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    // glTranslatef(0, 0, -15);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwWaitEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwTerminate();
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
      // Reload/regenerate image
      std::cout << "Reload" << std::endl;

      createImage(textureId, pixels, nx, ny, camera, sphereNormal);
    }
  }

  glfwTerminate();

  return 0;
}

void
createImage(GLuint& textureId, float* pixels, const size_t nx, const size_t ny,
            Camera* cam, Framebuffer (*gen_fb)(size_t, size_t, Camera*))
{
  glBindTexture(GL_TEXTURE_2D, textureId);

  // std::cout << "before render" << std::endl;
  Framebuffer fb(gen_fb(nx, ny, cam));
  // std::cout << "after render" << std::endl;

  framebufferToGLPixelArray(fb, pixels);
  // std::cout << "after pixel conversion" << std::endl;

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, nx, ny, 0, GL_RGB, GL_FLOAT,
               pixels);

  glBindTexture(GL_TEXTURE_2D, 0);
}

Framebuffer
sphereNormal(const size_t nx, const size_t ny, Camera* cam)
{
  Framebuffer fb(nx, ny);

  Sphere sph(Vec3d(0, 0, -2), 0.5);

  for (size_t i(0); i < nx; ++i) {
    for (size_t j(0); j < ny; ++j) {
      auto ray(cam->generateRay(i, j));

      HitStruct hit;

      Vec3f color(0.1, 0.1, 0.1);
      if (sph.closestHit(ray, hit)) {
        auto normal(sph.normal(hit.hitPoint()));

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