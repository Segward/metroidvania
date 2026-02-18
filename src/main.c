#include <glad/glad.h>
#include <engine/graphics/window.h>
#include <engine/graphics/quad.h>
#include <engine/graphics/texture.h>
#include <engine/global.h>

int main(void) {
  if (!window_init(800, 800, "metroidvania"))
    return 1;

  if (!quad_init())
    return 1;

  texture_t sprite = texture_create("assets/sprite.png");
  if (!sprite.valid)
      return 1;

  int columns = 4;
  int rows = 3;
  int frame_index = 2;

  int col = frame_index % columns;
  int row = frame_index / columns;

  float u0 = col / (float)columns;
  float u1 = (col + 1) / (float)columns;
  float v1 = 1.0f - (row / (float)rows);
  float v0 = 1.0f - ((row + 1) / (float)rows);
  vec4 uv = { u0, v0, u1, v1 };

  while (!glfwWindowShouldClose(global.window.handle)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    quad_draw((vec2){ 400, 400 }, (vec2){ 400, 400 }, 
              (vec4){ 1.0f, 1.0f, 1.0f, 1.0f}, sprite.id, uv);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  glfwDestroyWindow(global.window.handle);
  glfwTerminate();

  return 0;
}
