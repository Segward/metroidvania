#include <util/global.h>
#include <util/time.h>
#include <util/aabb.h>

#include <graphics/window.h>
#include <graphics/texture.h>

#include <graphics/quad.h>
#include <graphics/text.h>

#include <model/sprite.h>

static sprite_t player;
static sprite_t ground;

int main(void) 
{
  window_init(800, 800, "metroidvania");
  time_init();
  quad_init();
  text_init();

  texture_create(&global.texture.player, "assets/player.png");
  texture_white(&global.texture.white);

  sprite_create(&player, global.texture.white);
  sprite_create(&ground, global.texture.white);

  vec2_dup(player.position, (vec2){ 400.0f, 400.0f });
  vec2_dup(ground.position, (vec2){ 400.0f, 300.0f });

  vec2_dup(player.size, (vec2){ 100.0f, 100.0f });
  vec2_dup(ground.size, (vec2){ 600.0f, 100.0f });

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();

    float speed = global.time.delta_time * 200;
    if (glfwGetKey(global.window.handle, GLFW_KEY_W) == GLFW_PRESS)
      vec2_add(player.position, player.position, (vec2){ 0.0f, speed});
    if (glfwGetKey(global.window.handle, GLFW_KEY_A) == GLFW_PRESS)
      vec2_add(player.position, player.position, (vec2){ -speed, 0.0f});
    if (glfwGetKey(global.window.handle, GLFW_KEY_S) == GLFW_PRESS)
      vec2_add(player.position, player.position, (vec2){ 0.0f, -speed});
    if (glfwGetKey(global.window.handle, GLFW_KEY_D) == GLFW_PRESS)
      vec2_add(player.position, player.position, (vec2){ speed, 0.0f});

    aabb_collide_and_correct(player.position, player.size, ground.position, ground.size);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sprite_draw(&player);
    sprite_draw(&ground);

    text_draw("Hello player!", 
              (vec2){ 500.0f, 600.0f }, 0.5f, 
              (vec4){1.0f, 1.0f, 1.0f, 1.0f});

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  texture_delete(&global.texture.player);
  texture_delete(&global.texture.white);
  text_delete();
  quad_delete();
  window_close();

  return 0;
}
