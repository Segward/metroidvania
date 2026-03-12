#include <engine/model/camera.h>
#include <engine/graphics/window.h>

vec2 camera_pos;
mat4x4 camera_view;

void camera_update(void)
{
  mat4x4_identity(camera_view);

  float x = -camera_pos[0] + window_width * 0.5f;
  float y = -camera_pos[1] + window_height * 0.5f;

  mat4x4_translate_in_place(camera_view, x, y, 0.0f);
}
