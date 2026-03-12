#include <pch.h>
#include <engine/model/time.h>

double time_last;
double time_delta;

void time_init(void)
{
  time_last = glfwGetTime();
  time_delta = 0;
}

void time_update(void)
{
  double now = glfwGetTime();
  time_delta = now - time_last;
  time_last = now;
}
