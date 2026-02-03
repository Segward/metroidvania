#include <engine/global.h>
#include <engine/render.h>
#include <engine/quad.h>

int main() {
  render_init();

  while (!glfwWindowShouldClose(global.window.handle)) {
    render_begin();
    quad_draw(0.6f, 0.3f, 0.0f, 0.5f, 0.25f, 1.0f, 1.0f, 0.0f, 1.0f);
    render_end();
  }

  return 0;
}
