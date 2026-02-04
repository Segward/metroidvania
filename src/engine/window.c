#include <glad/glad.h>
#include <engine/window.h>
#include <engine/util.h>
#include <engine/global.h>

#define WINDOW_TITLE "metroidvania"

void window_init(u32 width, u32 height) {
  if (!glfwInit())
    ERROR_EXIT("glfw failed to initialize");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *handle = glfwCreateWindow(width, height, WINDOW_TITLE, NULL, NULL);
  if (handle == NULL) {
    glfwTerminate();
    ERROR_EXIT("glfw failed to create window");
  }

  glfwMakeContextCurrent(handle);
  glfwSwapInterval(0);

  if (!gladLoadGL()) {
    glfwTerminate();
    ERROR_EXIT("glad failed to load");
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  global.window.handle = handle;
  global.window.width = width;
  global.window.height = height;
}
