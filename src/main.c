#include <graphics/window.h>
#include <util/global.h>
#include <model/static_sprite.h>
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

  static_sprite_t sprite;
  if (!static_sprite_create(&sprite, "assets/sprite.png"))
    goto cleanup;

  success = 0;

  while (!glfwWindowShouldClose(global.window.handle)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static_sprite_draw(sprite);

    text_draw("Hello player!", 
              (vec2){ 500.0f, 600.0f },
              0.5f, 
              (vec4){1.0f, 1.0f, 1.0f, 1.0f});

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

cleanup:
  static_sprite_delete(&sprite);
  text_delete();
  quad_delete();
  window_close();

  return success;
}
