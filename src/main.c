#include <graphics/window.h>
#include <util/global.h>
#include <model/static_sprite.h>
#include <model/animated_sprite.h>
#include <shapes/quad.h>
#include <shapes/text.h>

int main(void) 
{
  int success = 1;

  if (!window_init(800, 800, "metroidvania"))
    goto cleanup;

  if (!quad_init())
    goto cleanup;

  if (!text_init())
    goto cleanup;

  animated_sprite_t animated_sprite;
  if (!animated_sprite_create(&animated_sprite, "assets/sprite.png", 4, 4))
    goto cleanup;

  animated_sprite_frame(&animated_sprite, 1, 1);
  animated_sprite_frame(&animated_sprite, 1, 2);

  success = 0;

  double last_time = glfwGetTime();

  while (!glfwWindowShouldClose(global.window.handle)) {
    double now = glfwGetTime();
    double delta = now - last_time;
    if (delta >= 0.5)
    {
      animated_sprite_next_frame(&animated_sprite);
      last_time = now;
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    animated_sprite_draw(&animated_sprite);

    text_draw("Hello player!", 
              (vec2){ 500.0f, 600.0f },
              0.5f, 
              (vec4){1.0f, 1.0f, 1.0f, 1.0f});

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

cleanup:

  animated_sprite_delete(&animated_sprite);
  text_delete();
  quad_delete();
  window_close();

  return success;
}
