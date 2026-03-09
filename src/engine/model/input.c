#include <engine/model/input.h>
#include <engine/model/global.h>

void input_update(void)
{
  global.input.left = glfwGetKey(global.window.handle, GLFW_KEY_A) == GLFW_PRESS;
  global.input.right = glfwGetKey(global.window.handle, GLFW_KEY_D) == GLFW_PRESS;
  global.input.up = glfwGetKey(global.window.handle, GLFW_KEY_W) == GLFW_PRESS;
  global.input.down = glfwGetKey(global.window.handle, GLFW_KEY_S) == GLFW_PRESS;
}
