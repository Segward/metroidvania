#include <pch.h>
#include <_graphics/_win.h>
#include <global.h>

static void window_size_callback(GLFWwindow* window, int width, int height)
{
  global.window.width = width;
  global.window.height = height;

  mat4x4_ortho(global.proj, 0.0f, width, 0.0f, height, -1.0f, 1.0f);
}

#define _WIN_WIDTH 800
#define _WIN_HEIGHT 800
#define _WIN_TITLE "metroidvania"

void win_init(void)
{
  assert(glfwInit());
  printf("GLFW version: %s\n", glfwGetVersionString());

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *handle = glfwCreateWindow(_WIN_WIDTH, _WIN_HEIGHT, _WIN_TITLE, NULL, NULL);
  assert(handle);

  glfwMakeContextCurrent(handle);
  glfwSwapInterval(0);
  glfwSetWindowSizeCallback(handle, window_size_callback);

  global.window.handle = handle;
  global.window.width = _WIN_WIDTH;
  global.window.height = _WIN_HEIGHT;

  mat4x4_ortho(global.proj, 0.0f, _WIN_WIDTH, 0.0f, _WIN_HEIGHT, -1.0f, 1.0f);
}

void win_cleanup(void)
{
  glfwDestroyWindow(global.window.handle);
  glfwTerminate();
}
