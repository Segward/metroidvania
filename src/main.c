#include <engine/quad.h>
#include <engine/text.h>
#include <engine/texture.h>
#include <engine/window.h>
#include <engine/global.h>

int main(void) {
  if (!window_init(800, 800, "metroidvania"))
    return 1;

  if (!quad_init())
    return 1;

  if (!text_init())
    return 1;

  GLuint tex = texture_create("assets/sprite.png");
  if (!tex) 
    return 1;

  while (!glfwWindowShouldClose(global.window.handle)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    quad_draw((vec2){ 400, 400}, 
              (vec2){ 50, 50},
              (vec4){ 1, 1, 1, 1},
              tex, (vec4){0, 0, 1, 1});

    text_draw("Hello player!", 
              (vec2){ 500, 600 },
              1, (vec4){1, 1, 1, 1});

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  window_close();

  return 0;
}
