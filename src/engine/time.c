#include <GLFW/glfw3.h>
#include <engine/time.h>
#include <engine/global.h>

void time_init(void) {
  global.time.last = glfwGetTime();
  global.time.now = glfwGetTime();
  global.time.delta = 0;
}

void time_update(void) {
  global.time.now = glfwGetTime();
  global.time.delta = global.time.now - global.time.last;
  global.time.last = global.time.now;
}
