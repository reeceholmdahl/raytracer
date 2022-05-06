#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

int
CheckGLErrors(const char* s)
{
  int errCount = 0;

  return errCount;
}

int
main(void)
{
  if (!glfwInit()) {
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int winWidth = 1000;
  float aspectRatio = 1.0;
  int winHeight = winWidth / aspectRatio;

  GLFWwindow* window =
    glfwCreateWindow(winWidth, winHeight, "OpenGL Example", NULL, NULL);
  if (!window) {
    std::cerr << "GLFW did not create a window!" << std::endl;

    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "GLEW Error! glewInit failed, exiting." << std::endl;
    exit(EXIT_FAILURE);
  }

  GLint major_version;
  glGetIntegerv(GL_MAJOR_VERSION, &major_version);
  std::cout << "OpenGL Major Version: " << major_version << std::endl;

  GLint minor_version;
  glGetIntegerv(GL_MINOR_VERSION, &minor_version);
  std::cout << "OpenGL Minor Version: " << minor_version << std::endl;

  GLfloat line_width;
  glGetFloatv(GL_LINE_WIDTH, &line_width);
  std::cout << "OpenGL Line Width: " << line_width << std::endl;

  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

  GLint maxTexture;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexture);
  std::cout << "Max texture size: " << maxTexture << std::endl;

  GLboolean depthTesting;
  glGetBooleanv(GL_DEPTH_TEST, &depthTesting);
  std::cout << "Depth testing enabled by default: " << depthTesting
            << std::endl;

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.9, 0.7, 0.15, 1.0);

  GLfloat* vertices =
    new GLfloat[9]{ -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };

  GLuint triangleVBO;
  glGenBuffers(1, &triangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
  delete[] vertices;
  vertices = nullptr;
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint triangleVAO;
  glGenVertexArrays(1, &triangleVAO);
  glBindVertexArray(triangleVBO);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  sivelab::GLSLObject shader;
  shader.addShader("C:/Users/rholm/Documents/Spring2022/CS4212/cs4212-renderer/"
                   "hardware-renderer/shaders/vertexShader_passthrough.glsl",
                   sivelab::GLSLObject::VERTEX_SHADER);
  shader.addShader("C:/Users/rholm/Documents/Spring2022/CS4212/cs4212-renderer/"
                   "hardware-renderer/shaders/fragmentShader_passthrough.glsl",
                   sivelab::GLSLObject::FRAGMENT_SHADER);
  shader.createProgram();

  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);

  double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;
  while (!glfwWindowShouldClose(window)) {

    // Clear the window's buffer (or clear the screen to our
    // background color)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.activate();

    glBindVertexArray(triangleVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    shader.deactivate();

    endFrameTime = glfwGetTime();
    timeDiff = endFrameTime - startFrameTime;
    startFrameTime = glfwGetTime();

    // Swap the front and back buffers
    glfwSwapInterval(0);
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, 1);
    } else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
      std::cout << (1 / timeDiff) << " frames per second (estimate)"
                << std::endl;
    }
  }

  glfwTerminate();
  return 0;
}
