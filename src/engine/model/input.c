#include <engine/model/input.h>
#include <engine/model/global.h>

void input_update(void)
{
  global.input.left = glfwGetKey(global.window.handle, GLFW_KEY_A) == GLFW_PRESS;
  global.input.right = glfwGetKey(global.window.handle, GLFW_KEY_D) == GLFW_PRESS;
  global.input.up = glfwGetKey(global.window.handle, GLFW_KEY_W) == GLFW_PRESS;
  global.input.down = glfwGetKey(global.window.handle, GLFW_KEY_S) == GLFW_PRESS;

  global.input.mouse_left = glfwGetMouseButton(global.window.handle, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
  global.input.mouse_right = glfwGetMouseButton(global.window.handle, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

  double x, y;
  glfwGetCursorPos(global.window.handle, &x, &y);
  vec2_dup(global.input.mouse_pos, (vec2){ (float)x, (float)y });

  float flipped_y = global.window.height - (float)y;
  global.input.mouse_world[0] = (float)x + global.camera.pos[0] - global.window.width * 0.5f;
  global.input.mouse_world[1] = flipped_y + global.camera.pos[1] - global.window.height * 0.5f;
}
