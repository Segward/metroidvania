#include <engine/model/camera.h>
#include <engine/model/global.h>

void camera_init(vec2 pos)
{
  vec2_dup(global.camera.pos, pos);
}

void camera_update(void)
{
  mat4x4_identity(global.view);

  float x = -global.camera.pos[0] + global.window.width * 0.5f;
  float y = -global.camera.pos[1] + global.window.height * 0.5f;

  mat4x4_translate_in_place(global.view, x, y, 0.0f);
}
