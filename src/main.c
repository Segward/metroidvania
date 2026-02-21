#include <glad/glad.h>
#include <engine/window.h>
#include <engine/quad.h>
#include <engine/animation.h>
#include <engine/global.h>

int main(void) {
  if (!window_init(800, 800, "metroidvania"))
    return 1;

  if (!quad_init())
    return 1;

  animation_t animation = animation_create("assets/sprite.png", 4, 4);
  if (!animation.valid)
    return 1;

  double last_time = glfwGetTime();
  double frame_delay = 0.1;

  while (!glfwWindowShouldClose(global.window.handle)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double current_time = glfwGetTime();
    if (current_time - last_time >= frame_delay) {
      animation_next(&animation);
      last_time = current_time;
    }

    quad_draw((vec2){ 400, 400 }, (vec2){ 400, 400 }, 
              (vec4){ 1.0f, 1.0f, 1.0f, 1.0f}, 
              animation.texture.id, animation.uv);

    quad_draw((vec2){ 300, 200 }, (vec2){ 300, 300 }, 
              (vec4){ 0.5f, 0.5f, 1.0f, 1.0f}, 
              animation.texture.id, animation.uv);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  glfwDestroyWindow(global.window.handle);
  glfwTerminate();

  return 0;
}
