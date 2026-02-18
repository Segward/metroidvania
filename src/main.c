#include <glad/glad.h>
#include <engine/graphics/window.h>
#include <engine/graphics/quad.h>
#include <engine/global.h>

int main(void) {
  if (!window_init(800, 600, "metroidvania"))
    return 1;

  if (!quad_init())
    return 1;

  while (!glfwWindowShouldClose(global.window.handle)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    quad_draw((vec2){ 400, 300 }, (vec2){ 50, 50 }, (vec4){ 1.0f, 1.0f, 1.0f, 1.0f});

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  glfwDestroyWindow(global.window.handle);
  glfwTerminate();

  return 0;
}
