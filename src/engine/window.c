#include <glad/glad.h>
#include <engine/window.h>
#include <engine/global.h>

#include <stdio.h>

static void window_size_callback(GLFWwindow *window, int width, int height) {
  global.window.width = width;
  global.window.height = height;
}

int window_init(unsigned width, unsigned height) {
  if (!glfwInit()) {
    fprintf(stderr, "failed to initialize glfw\n");
    return 0;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *handle = glfwCreateWindow(width, height, "metroidvania", NULL, NULL);
  if (handle == NULL) {
    fprintf(stderr, "failed to create window\n");
    glfwTerminate();
    return 0;
  }

  glfwMakeContextCurrent(handle);
  glfwSwapInterval(0);

  if (!gladLoadGL()) {
    fprintf(stderr, "failed to load glad\n");
    glfwTerminate();
    return 0;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  global.window.handle = handle;
  global.window.width = width;
  global.window.height = height;

  glfwSetWindowSizeCallback(handle, window_size_callback);

  return 1;
}
