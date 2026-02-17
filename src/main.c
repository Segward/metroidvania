#include <engine/gfx/render.h>
#include <engine/global.h>
#include <engine/time.h>
#include <engine/physics.h>

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  if (!render_init()) {
    fprintf(stderr, "failed to initialize renderer\n");
    return 0;
  }

  time_init();
  physics_init();

  for (size_t i = 0; i < 20; i++) {
    size_t index;
    physics_object_create((vec2){ rand() % (global.window.width - 50), rand() % (global.window.height - 5) }, 
                          (vec2){ 50, 50 }, &index);
    object_t *object = physics_object_get(index);
    object->acceleration[0] = rand() % 200 - 100;
    object->acceleration[1] = rand() % 200 - 100;
  }

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();
    physics_update();
    render_begin();

    for (size_t i = 0; i < 20; i++) {
      object_t *object = physics_object_get(i);
      render_quad((vec2){ object->aabb.position[0] , object->aabb.position[1] }, 
                  (vec2){ 50, 50 }, (vec4){ 0.0f, 1.0f, 0.0f, 1.0f });

      if (object->aabb.position[0] + object->aabb.size[0] / 2 > global.window.width || object->aabb.position[0] - object->aabb.size[0] / 2 < 0)
        object->velocity[0] *= -1;
      if (object->aabb.position[1] + object->aabb.size[1] / 2 > global.window.height || object->aabb.position[1] - object->aabb.size[1] / 2 < 0)
        object->velocity[1] *= -1;

      if (object->velocity[0] > 500)
        object->velocity[0] = 500;
      if (object->velocity[0] < -500)
        object->velocity[0] = -500;

      if (object->velocity[1] > 500)
        object->velocity[1] = 500;
      if (object->velocity[1] < -500)
        object->velocity[1] = -500;
    }

    render_end();
  }

  glfwDestroyWindow(global.window.handle);
  glfwTerminate();

  return 1;
}
