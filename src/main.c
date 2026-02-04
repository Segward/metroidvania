#include <engine/render.h>
#include <engine/global.h>
#include <engine/time.h>
#include <engine/physics.h>
#include <stdlib.h>

int main(void) {
  render_init();
  time_init();
  physics_init();

  for (usize i = 0; i < 20; i++) {
    usize index;
    physics_object_create((vec2){ rand() % global.window.width, rand() % global.window.height }, 
                          (vec2){ 100, 100 }, &index);
    object_t *object = physics_object_get(index);
    object->acceleration[0] = rand() % 200 - 100;
    object->acceleration[1] = rand() % 200 - 100;
  }

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();
    physics_update();
    render_begin();

    for (usize i = 0; i < 20; i++) {
      object_t *object = physics_object_get(i);
      render_quad((vec2){ object->aabb.position[0] , object->aabb.position[1] }, 
                  (vec2){ 50, 50 }, (vec4){ 0.0f, 1.0f, 0.0f, 1.0f });

      if (object->aabb.position[0] > global.window.width || object->aabb.position[0] < 0)
        object->velocity[0] *= -1;
      if (object->aabb.position[1] > global.window.height || object->aabb.position[1] < 0)
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

  return 0;
}
