#include <model/quad_batch.h>

#include <util/time.h>
#include <global.h>

#include <graphics/gl.h>
#include <graphics/win.h>
#include <graphics/quad.h>
#include <graphics/tex.h>

static quad_batch_t batch;

int main(void) 
{
  win_init();
  gl_init();
  quad_init();

  tex_create(&global.tex.player, "assets/textures/player.png");
  tex_create(&global.tex.grass, "assets/textures/grass.jpg");
  tex_white(&global.tex.white);

  mat4x4_identity(global.view);
  vec4_dup(global.tint, (vec4){ 1.0f, 1.0f, 1.0f, 1.0f });

  quad_batch_init(&batch, global.tex.white);
  quad_batch_push(&batch, (quad_t){ 
    .offset = { 0.0f, 0.0f },
    .size = { 50.0f, 50.0f },
    .color = { 1.0f, 1.0f, 1.0f, 1.0f }
  });

  quad_batch_push(&batch, (quad_t){ 
    .offset = { 100.0f, 50.0f },
    .size = { 50.0f, 100.0f },
    .color = { 1.0f, 1.0f, 1.0f, 1.0f }
  });

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    quad_batch_draw(&batch);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  quad_batch_cleanup(&batch);

  glDeleteTextures(1, &global.tex.white);
  glDeleteTextures(1, &global.tex.grass);
  glDeleteTextures(1, &global.tex.player);

  quad_cleanup();
  win_cleanup();

  return 0;
}
