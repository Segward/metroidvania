#include <engine/model/camera.h>
#include <engine/model/global.h>
#include <engine/model/input.h>
#include <engine/model/time.h>
#include <engine/model/sprite_batch.h>

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

  sprite_batch_t batch;
  sprite_batch_make(&batch, &tiles);

  while (!glfwWindowShouldClose(global.window.handle)) {
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

    sprite_batch_clear(&batch);
    sprite_batch_push(&batch, (sprite_t){
      .offset = { 0.0f, 0.0f },
      .size = { 500.0f, 500.0f },
      .color = { 1.0f, 1.0f, 1.0f, 1.0f },
      .atlas_start = { 0.0f, 0.0f },
      .atlas_size = { tiles.width, tiles.height }
    });

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sprite_batch_draw(&batch);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
    input_update();
  }

  glDeleteTextures(1, &tiles.id);

  sprite_cleanup();
  window_cleanup();

  return 0;
}
