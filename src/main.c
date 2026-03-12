#include <engine/model/camera.h>
#include <engine/model/time.h>

#include <engine/graphics/window.h>
#include <engine/graphics/sprite.h>
#include <engine/graphics/texture.h>

int main(void) 
{
  window_init(800, 800, "test");
  sprite_init();
  time_init();

  vec2_dup(camera_pos, (vec2){ 0.0f, 0.0f });

  while (!glfwWindowShouldClose(window_handle)) 
  {
    time_update();
    camera_update();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window_handle);
    glfwPollEvents();
  }

  sprite_cleanup();
  window_cleanup();

  return 0;
}
