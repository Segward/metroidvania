#include <glad/glad.h>
#include <engine/text.h>
#include <engine/window.h>
#include <engine/global.h>

int main(void) {
  if (!window_init(800, 800, "metroidvania"))
    return 1;

  if (!text_init())
    return 1;

  while (!glfwWindowShouldClose(global.window.handle)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    text_draw("Hello, World!", 
              (vec2){ 400.0f, 400.0f }, 0.5f, 
              (vec4){ 1.0f, 1.0f, 1.0f, 1.0f });

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  glfwDestroyWindow(global.window.handle);
  glfwTerminate();

  return 0;
}
