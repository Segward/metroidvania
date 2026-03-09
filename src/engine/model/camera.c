#include <engine/model/camera.h>
#include <global.h>

void camera_set(vec2 pos)
{
  mat4x4_identity(global.view);

  float x = -pos[0] + global.window.width * 0.5f;
  float y = -pos[1] + global.window.height * 0.5f;

  mat4x4_translate_in_place(global.view, x, y, 0.0f);
}
