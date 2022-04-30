#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "RayTracer.hpp"

using namespace renderer;

GLFWwindow *window;
GLuint tex;
float *pixels;
int _camera = 0;

constexpr float vertices[] = {
    1.0, 1.0, // top right corner
    0.0, 1.0, // top left corner
    0.0, 0.0, // bottom left corner
    1.0, 0.0  // bottom right corner
};

constexpr float texcoords[] = {
    1.0, 1.0, // top right corner
    0.0, 1.0, // top left corner
    0.0, 0.0, // bottom left corner
    1.0, 0.0  // bottom right corner
};

void renderer::initOpenGL(const size_t windowWidth, const size_t windowHeight, const std::string &title)
{
    // Create window
    window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);

    // Crash with error code
    if (!window)
    {
        std::cerr << "Error creating GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    GLenum err(glewInit());
    if (err != GLEW_OK)
    {
        std::cerr << "Error initializing GLEW" << std::endl;
        exit(-1);
    }

    // Configure window
    glViewport(0, 0, windowWidth, windowHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION);                 // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity();                            // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0., 1., 0., 1., 0., 1.);             // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW);                  // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity();

    glGenTextures(1, &tex);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void renderer::generateTexture(const Framebuffer &fb)
{
    glBindTexture(GL_TEXTURE_2D, tex);

    framebufferToGLPixelArray(fb, pixels);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, fb.width(), fb.height(), 0, GL_RGB, GL_FLOAT, pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void renderer::drawFrame()
{
    // Reset modelview matrix to identity
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Render OpenGL here
    glBindTexture(GL_TEXTURE_2D, tex);
    glEnableClientState(GL_VERTEX_ARRAY_EXT);    // tell OpenGL that you're using a vertex array for fixed-function attribute
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); // tell OpenGL that you're using a vertex array for fixed-function attribute
    glVertexPointer(2, GL_FLOAT, 0, vertices);   // point to the vertices to be used
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_QUADS, 0, 4);          // draw the vertixes
    glDisableClientState(GL_VERTEX_ARRAY); // tell OpenGL that you're finished using the vertex arrayattribute
    glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Swap front and back buffers
    glfwSwapBuffers(window);
}

void renderer::changeCamera(const int camera)
{
    _camera = camera;
}

void renderer::handleInput(
    const bool rerenderScene,
    const bool openNewScene,
    const bool exportScene,
    const bool changeRenderSize,
    const bool prevCamera,
    const bool nextCamera)
{
}