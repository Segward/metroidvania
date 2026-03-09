#include <engine/model/camera.h>
#include <engine/model/layer.h>
#include <engine/model/global.h>

#include <engine/graphics/window.h>
#include <engine/graphics/sprite.h>
#include <engine/graphics/texture.h>

static layer_t layer;

int main(void) 
{
  window_init(800, 800, "test");
  sprite_init();

  texture_load_file(&global.tex.player, "assets/textures/player.png");
  texture_load_file(&global.tex.grass, "assets/textures/grass.jpg");

  sprite_t player = {
    .offset = { 0.0f, 0.0f },
    .size = { 50.0f, 50.0f },
    .color = { 1.0f, 1.0f, 1.0f, 1.0f }
  };

  sprite_t grass1 = {
    .offset = { -50.0f, 100.0f },
    .size = { 50.0f, 50.0f },
    .color = { 1.0f, 1.0f, 1.0f, 1.0f }
  };

  sprite_t grass2 = {
    .offset = { 0.0f, 150.0f },
    .size = { 50.0f, 50.0f },
    .color = { 1.0f, 1.0f, 1.0f, 1.0f }
  };

  layer_make(&layer, 0);
  layer_push_sprite(&layer, player, global.tex.player);
  layer_push_sprite(&layer, grass1, global.tex.grass);
  layer_push_sprite(&layer, grass2, global.tex.grass);

  while (!glfwWindowShouldClose(global.window.handle)) {
    camera_set((vec2){ 0.0f, 0.0f });

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    layer_draw(&layer);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  layer_cleanup(&layer);

  glDeleteTextures(1, &global.tex.grass);
  glDeleteTextures(1, &global.tex.player);

  sprite_cleanup();
  window_cleanup();

  return 0;
}
