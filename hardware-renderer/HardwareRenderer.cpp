#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

  int winWidth = 1280;
  float aspectRatio = 16 / 9.f;
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
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glClearColor(0.9, 0.7, 0.15, 1.0);

  std::ifstream inputFile("./bunnyVertexData.json");
  json j;
  inputFile >> j;

  std::cout << j.size() << std::endl;

  // Triangle vertex buffer
  // GLfloat* h_vertexBuffer = new GLfloat[36]{
  //   -0.5f, -0.5f, 0.f, 0.0f, 1.0f, 1.0f, // v1, color
  //   0.5f,  -0.5f, 0.f, 1.0f, 0.0f, 1.0f, // v2, color
  //   0.0f,  0.5f,  0.f, 1.0f, 1.0f, 0.0f, // v3, color
  //   0.5f,  -1.0f, 0.f, 1.0f, 0.0f, 0.0f, // v1, color
  //   1.5f,  -1.0f, 0.f, 0.0f, 1.0f, 0.0f, // v2, color
  //   1.0f,  0.0f,  0.f, 0.0f, 0.0f, 1.0f  // v3, color
  // };

  const size_t k_vertexBufferSize = 1253988;
  GLfloat* h_vertexBuffer = new GLfloat[k_vertexBufferSize];
  for (int i(0); i < j.size(); ++i) {
    h_vertexBuffer[i] = j[i];
  }

  // Spatial bounds for ortho matrix
  float left = -7.5;
  float right = 7.5;
  float bottom = -4.2;
  float top = 4.2;
  float near = -10.0;
  float far = 10.0;

  const size_t k_glFloatSize = sizeof(GLfloat);

  glm::mat4 identity = glm::mat4(1.f);
  glm::mat4 modelMatrix = glm::mat4(1.f);
  glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 4.f),
                                     glm::vec3(0.f, 0.f, -1.f),
                                     glm::vec3(0.f, 1.f, 0.f));
  // glm::mat4 projMatrix = glm::ortho(left, right, top, bottom, near, far);
  glm::mat4 projMatrix = glm::perspective(45.f, 16 / 9.f, 0.1f, 100.f);

  GLuint id_triangleVBO;
  glGenBuffers(1, &id_triangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, id_triangleVBO);
  glBufferData(GL_ARRAY_BUFFER,
               k_vertexBufferSize * k_glFloatSize,
               h_vertexBuffer,
               GL_STATIC_DRAW);
  delete[] h_vertexBuffer;
  h_vertexBuffer = nullptr;
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint id_triangleVAO;
  glGenVertexArrays(1, &id_triangleVAO);
  glBindVertexArray(id_triangleVBO);
  glEnableVertexAttribArray(0); // position
  glEnableVertexAttribArray(1); // color

  glBindBuffer(GL_ARRAY_BUFFER, id_triangleVBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * k_glFloatSize, 0);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        6 * k_glFloatSize,
                        (const GLvoid*)(3 * k_glFloatSize));

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
  GLuint id_projMatrix = shader.createUniform("projMatrix");
  GLuint id_viewMatrix = shader.createUniform("viewMatrix");
  GLuint id_modelMatrix = shader.createUniform("modelMatrix");
  shader.activate();
  glUniformMatrix4fv(id_projMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix));
  glUniformMatrix4fv(id_viewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  glUniformMatrix4fv(id_modelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
  shader.deactivate();

  float angle = 0.f;
  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);
  glMatrixMode(GL_MODELVIEW);

  double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;
  while (!glfwWindowShouldClose(window)) {

    // Clear the window's buffer (or clear the screen to our
    // background color)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.activate();
    glUniformMatrix4fv(
      id_modelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(id_triangleVAO);
    glDrawArrays(GL_TRIANGLES, 0, k_vertexBufferSize / 6);
    glBindVertexArray(0);

    shader.deactivate();

    endFrameTime = glfwGetTime();
    timeDiff = endFrameTime - startFrameTime;
    startFrameTime = glfwGetTime();

    // Swap the front and back buffers
    // glfwSwapInterval(0);
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, 1);
    } else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
      std::cout << (1 / timeDiff) << " est. frames/sec" << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
      angle += 0.3f;
      modelMatrix =
        glm::rotate(identity, glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));

    } else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
      angle -= 0.3f;
      modelMatrix =
        glm::rotate(identity, glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));
    }
  }

  glfwTerminate();
  return 0;
}
