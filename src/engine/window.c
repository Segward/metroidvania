#include <glad/glad.h>
#include <engine/window.h>
#include <engine/global.h>
#include <engine/util.h>

void window_size_callback(GLFWwindow *window, int width, int height) {
  global.window.width = width;
  global.window.height = height;
}

void window_init(void) {
  if (!glfwInit())
    ERROR_EXIT(1, "glfw failed initializing\n");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *handle = glfwCreateWindow(640, 480, "Topdown", NULL, NULL);
  if (handle == NULL)
    ERROR_EXIT(1, "glfw failed creating window\n");

  glfwMakeContextCurrent(handle);
  glfwSwapInterval(0);

  glfwSetWindowSizeCallback(handle, window_size_callback);
  global.window.handle = handle;

  if (!gladLoadGL())
    ERROR_EXIT(1, "glad failed loading\n");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
