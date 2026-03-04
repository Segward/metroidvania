#include <pch.h>
#include <_graphics/_gl.h>

void gl_init(void)
{
  assert(gladLoadGL());
  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}
