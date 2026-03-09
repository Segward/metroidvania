#include <engine/graphics/window.h>
#include <engine/model/global.h>

static void window_size_callback(GLFWwindow* window, int width, int height)
{
  global.window.width = width;
  global.window.height = height;

  mat4x4_ortho(global.proj, 0.0f, width, 0.0f, height, -1.0f, 1.0f);
}

void window_init(int width, int height, const char *title)
{
  assert(glfwInit());
  printf("GLFW version: %s\n", glfwGetVersionString());

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *handle = glfwCreateWindow(width, height, title, NULL, NULL);
  assert(handle);

  glfwMakeContextCurrent(handle);
  glfwSwapInterval(0);
  glfwSetWindowSizeCallback(handle, window_size_callback);

  global.window.handle = handle;
  global.window.width = width;
  global.window.height = height;

  mat4x4_ortho(global.proj, 0.0f, width, 0.0f, height, -1.0f, 1.0f);

  assert(gladLoadGL());
  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}

void window_cleanup(void)
{
  glfwDestroyWindow(global.window.handle);
  glfwTerminate();
}
