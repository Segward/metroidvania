#include <engine/model/sprite_batch.h>
#include <engine/util/time.h>
#include <global.h>

#include <engine/graphics/window.h>
#include <engine/graphics/sprite.h>
#include <engine/graphics/texture.h>

static sprite_batch_t grass;
static sprite_batch_t entities;

int main(void) 
{
  window_init(800, 800, "test");
  sprite_init();

  mat4x4_identity(global.view);

  texture_load_file(&global.tex.player, "assets/textures/player.png");
  texture_load_file(&global.tex.grass, "assets/textures/grass.jpg");

  sprite_batch_make(&grass, global.tex.grass);

  sprite_t *sprite = sprite_batch_push(&grass, (sprite_t){
    .offset = { 200.0f, 400.0f },
    .size = { 400.0f, 50.0f },
    .color = { 1.0f, 1.0f, 1.0f, 1.0f }
  });

  sprite = sprite_batch_push(&grass, (sprite_t){
    .offset = { 600.0f, 400.0f },
    .size = { 100.0f, 100.0f },
    .color = { 1.0f, 1.0f, 1.0f, 1.0f }
  });

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sprite_batch_draw(&grass);
    sprite_batch_draw(&entities);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  sprite_batch_cleanup(&grass);

  glDeleteTextures(1, &global.tex.white);
  glDeleteTextures(1, &global.tex.grass);
  glDeleteTextures(1, &global.tex.player);

  sprite_cleanup();
  window_cleanup();

  return 0;
}
