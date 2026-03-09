#include <engine/model/camera.h>
#include <engine/model/layer.h>
#include <engine/model/global.h>
#include <engine/model/input.h>
#include <engine/model/time.h>

#include <engine/graphics/window.h>
#include <engine/graphics/sprite.h>
#include <engine/graphics/texture.h>

int main(void) 
{
  window_init(800, 800, "test");
  sprite_init();
  time_init();

  texture_load_file(&global.texture.grass, "assets/textures/grass.jpg");
  texture_load_file(&global.texture.player, "assets/textures/player.png");

  sprite_t grass1 = {
    .offset = { -50.0f, 100.0f },
    .size = { 50.0f, 50.0f },
    .color = { 0.2f, 0.5f, 1.0f, 1.0f }
  };

  sprite_t grass2 = {
    .offset = { 0.0f, 150.0f },
    .size = { 50.0f, 50.0f },
    .color = { 1.0f, 1.0f, 1.0f, 1.0f }
  };
  sprite_t player = {
    .offset = { 0.0f, 0.0f },
    .size = { 50.0f, 50.0f },
    .color = { 1.0f, 1.0f, 1.0f, 1.0f }
  };

  layer_t grass_layer;
  layer_t player_layer;

  layer_make(&grass_layer, 0);
  layer_make(&player_layer, 1);

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();
    camera_update(player.offset);

    if (global.input.left)
      player.offset[0] -= global.time.delta * 200;

    if (global.input.right)
      player.offset[0] += global.time.delta * 200;

    if (global.input.up)
      player.offset[1] += global.time.delta * 200;

    if (global.input.down)
      player.offset[1] -= global.time.delta * 200;

    layer_clear(&grass_layer);
    layer_clear(&player_layer);

    layer_push(&grass_layer, grass1, global.texture.grass);
    layer_push(&grass_layer, grass2, global.texture.grass);
    layer_push(&player_layer, player, global.texture.player);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    layer_draw(&grass_layer);
    layer_draw(&player_layer);
 
    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
    input_update();
  }

  layer_cleanup(&grass_layer);
  layer_cleanup(&player_layer);

  glDeleteTextures(1, &global.texture.grass);
  glDeleteTextures(1, &global.texture.player);

  sprite_cleanup();
  window_cleanup();

  return 0;
}
