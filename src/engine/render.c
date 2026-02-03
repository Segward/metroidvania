#include <glad/glad.h>
#include <engine/render.h>
#include <engine/global.h>
#include <engine/window.h>
#include <engine/quad.h>

void render_init(void) {
  window_init();
  quad_init();
}

void render_begin(void) {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void render_end(void) {
  glfwSwapBuffers(global.window.handle);
  glfwPollEvents();
}
