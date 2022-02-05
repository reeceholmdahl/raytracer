#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer_app.hpp"

using namespace renderer;

GLFWwindow *window;
GLuint tex;
float *pixels;

void renderer::initOpenGL(const size_t windowWidth, const size_t windowHeight, const std::string &title)
{
    // Create window
    window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);

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