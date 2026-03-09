#include <pch.h>
#include <engine/model/time.h>
#include <engine/model/global.h>

void time_init(void)
{
  global.time.last_time = glfwGetTime();
  global.time.delta_time = 0;
}

void time_update(void)
{
  double now = glfwGetTime();
  global.time.delta_time = now - global.time.last_time;
  global.time.last_time = now;
}
