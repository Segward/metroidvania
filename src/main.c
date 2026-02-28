#include <global.h>

#include <shapes/quad.h>
#include <shapes/text.h>

#include <graphics/texture.h>
#include <graphics/window.h>

int main(void) {
  if (!window_init(800, 800, "metroidvania"))
    return 1;

  if (!quad_init())
    return 1;

  if (!text_init())
    return 1;

  GLuint texture = texture_create("assets/sprite.png");
  if (!texture) 
    return 1;

  while (!glfwWindowShouldClose(global.window.handle)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    quad_draw((vec2){ 400.0f, 400.0f}, 
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

  texture_delete(&texture);
  text_delete();
  quad_delete();
  window_close();

  return 0;
}
