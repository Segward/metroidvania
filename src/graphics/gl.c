#include <pch.h>
#include <graphics/gl.h>

void gl_init(void)
{
  assert(gladLoadGL());
  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}
