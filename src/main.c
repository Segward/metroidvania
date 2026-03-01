#include <util/global.h>

#include <shapes/sprite.h>
#include <shapes/text.h>

#include <graphics/texture.h>
#include <graphics/window.h>

int main(void) 
{
  int success = 1;

  if (!window_init(800, 800, "metroidvania"))
    goto cleanup;

  if (!sprite_init())
    goto cleanup;

  if (!text_init())
    goto cleanup;

  GLuint texture;
  if (!texture_create(&texture, "assets/sprite.png"))
    goto cleanup;

  success = 0;

  while (!glfwWindowShouldClose(global.window.handle)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sprite_draw((vec2){ 400.0f, 400.0f}, 
                (vec2){ 200.0f, 200.0f},
                (vec4){ 1.0f, 1.0f, 1.0f, 1.0f},
                texture, 
                (vec4){0.0f, 0.0f, 1.0f, 1.0f});

    text_draw("Hello player!", 
              (vec2){ 500.0f, 600.0f },
              0.5f, 
              (vec4){1.0f, 1.0f, 1.0f, 1.0f});

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

cleanup:
  texture_delete(&texture);
  text_delete();
  sprite_delete();
  window_close();

  return success;
}
