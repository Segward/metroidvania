#include <graphics/window.h>
#include <util/global.h>
#include <model/sprite.h>
#include <util/animation.h>
#include <graphics/texture.h>
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

  animation_t animation;
  animation_create(&animation, 4, 4);

  animation_frame(&animation, 1, 1);
  animation_frame(&animation, 2, 1);
  animation_frame(&animation, 3, 1);
  animation_frame(&animation, 4, 1);

  GLuint texture;
  if (!texture_create(&texture, "assets/sprite.png"))
    goto cleanup;

  sprite_t sprite;
  sprite_create(&sprite, texture);
  sprite_apply_animation(&sprite, &animation);

  success = 0;

  double last_time = glfwGetTime();

  while (!glfwWindowShouldClose(global.window.handle)) {
    double now = glfwGetTime();
    double delta = now - last_time;
    if (delta >= 0.5)
    {
      sprite_update(&sprite, sprite.position, sprite.size); 
      last_time = now;
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sprite_draw(&sprite);

    text_draw("Hello player!", 
              (vec2){ 500.0f, 600.0f }, 0.5f, 
              (vec4){1.0f, 1.0f, 1.0f, 1.0f});

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

cleanup:

  animation_delete(&animation);
  texture_delete(&texture);
  text_delete();
  quad_delete();
  window_close();

  return success;
}
