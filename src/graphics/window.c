#include <pch.h>
#include <graphics/window.h>
#include <util/global.h>

static void window_size_callback(GLFWwindow* window, int width, int height)
{
  global.window.width = width;
  global.window.height = height;

  mat4x4_ortho(global.window.projection, 0.0f, width, 0.0f, height, -1.0f, 1.0f);
}

void window_init(int width, int height, const char *title) 
{
  assert(glfwInit());

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *handle = glfwCreateWindow(width, height, title, NULL, NULL);
  assert(handle);

  glfwMakeContextCurrent(handle);
  glfwSwapInterval(0);
  glfwSetWindowSizeCallback(handle, window_size_callback);

  assert(gladLoadGL());
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  global.window.handle = handle;
  global.window.width = width;
  global.window.height = height;

  mat4x4_ortho(global.window.projection, 0.0f, width, 0.0f, height, -1.0f, 1.0f);
}

void window_close(void)
{
  glfwDestroyWindow(global.window.handle);
  glfwTerminate();
}
