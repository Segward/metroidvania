#include <engine/model/camera.h>
#include <engine/model/global.h>
#include <engine/model/input.h>
#include <engine/model/time.h>
#include <engine/model/layer.h>

#include <engine/graphics/window.h>
#include <engine/graphics/sprite.h>
#include <engine/graphics/texture.h>

int main(void) 
{
  window_init(800, 800, "test");
  sprite_init();
  time_init();
  camera_init((vec2){ 0.0f, 0.0f });

  texture_t tiles;
  texture_load_file(&tiles, "assets/textures/tiles.png");

  layer_t layer;
  layer_make(&layer, &tiles);

  while (!glfwWindowShouldClose(global.window.handle)) 
  {
    time_update();
    camera_update();

    if (global.input.left)
      global.camera.pos[0] -= global.time.delta * 200;

    if (global.input.right)
      global.camera.pos[0] += global.time.delta * 200;

    if (global.input.down)
      global.camera.pos[1] -= global.time.delta * 200;

    if (global.input.up)
      global.camera.pos[1] += global.time.delta * 200;

    if (global.input.mouse_left)
    {
      sprite_t *sprite = layer_make_sprite(&layer);
      vec2_dup(sprite->offset, global.input.mouse_world);
      vec2_dup(sprite->size, (vec2){ 50.0f, 50.0f });
      vec4_dup(sprite->color, (vec4){ 1.0f, 1.0f, 1.0f, 1.0f });
      vec2_dup(sprite->atlas_start, (vec2){ 0.0f, 0.0f });
      vec2_dup(sprite->atlas_size, (vec2){ 64.0f, 64.0f });
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    layer_draw(&layer);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
    input_update();
  }

  layer_cleanup(&layer);

  glDeleteTextures(1, &tiles.id);

  sprite_cleanup();
  window_cleanup();

  return 0;
}
