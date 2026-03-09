#include <pch.h>
#include <engine/model/time.h>
#include <engine/model/global.h>

void time_init(void)
{
  global.time.last = glfwGetTime();
  global.time.delta = 0;
}

void time_update(void)
{
  double now = glfwGetTime();
  global.time.delta = now - global.time.last;
  global.time.last = now;
}
