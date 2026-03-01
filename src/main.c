#include <graphics/window.h>
#include <util/global.h>
#include <util/time.h>
#include <graphics/texture.h>
#include <shapes/quad.h>
#include <shapes/text.h>
#include <model/player.h>

int main(void) 
{
  if (!window_init(800, 800, "metroidvania"))
    goto cleanup;

  if (!quad_init())
    goto cleanup;

  if (!text_init())
    goto cleanup;

  if (!texture_init())
    goto cleanup;

  player_init();
  time_init();

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();
    player_update();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    player_draw();

    text_draw("Hello player!", 
              (vec2){ 500.0f, 600.0f }, 0.5f, 
              (vec4){1.0f, 1.0f, 1.0f, 1.0f});

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

cleanup:

  player_cleanup();
  texture_cleanup();
  text_delete();
  quad_delete();
  window_close();

  return 0;
}
