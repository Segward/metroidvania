#include <util/global.h>
#include <util/time.h>

#include <graphics/window.h>
#include <graphics/texture.h>

#include <graphics/quad.h>

#include <model/object.h>

static object_t player;
static object_t ground;

int main(void) 
{
  window_init(800, 800, "metroidvania");
  time_init();
  quad_init();

  texture_create(&global.texture.player, "assets/textures/player.png");
  texture_white(&global.texture.white);
  vec4_dup(global.tint, (vec4){ 1.0f, 1.0f, 1.0f, 1.0f });

  object_create(&player, global.texture.player);
  vec2_dup(player.position, (vec2){ 400.0f, 400.0f });
  vec2_dup(player.size, (vec2){ 100.0f, 100.0f });

  object_create(&ground, global.texture.white);
  vec2_dup(ground.position, (vec2){ 400.0f, 300.0f });
  vec2_dup(ground.size, (vec2){ 300.0f, 100.0f });

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();

    float halfW = global.window.width  * 0.5f;
    float halfH = global.window.height * 0.5f;

    float playerCenterX = player.position[0] + player.size[0] * 0.5f;
    float playerCenterY = player.position[1] + player.size[1] * 0.5f;

    mat4x4_identity(global.view);
    mat4x4_translate(global.view,
      -playerCenterX + halfW,
      -playerCenterY + halfH,
      0.0f);

    float speed = global.time.delta_time * 200;
    if (glfwGetKey(global.window.handle, GLFW_KEY_W) == GLFW_PRESS)
      player.position[1] += speed;

    if (glfwGetKey(global.window.handle, GLFW_KEY_A) == GLFW_PRESS)
      player.position[0] -= speed;

    if (glfwGetKey(global.window.handle, GLFW_KEY_S) == GLFW_PRESS)
      player.position[1] -= speed;

    if (glfwGetKey(global.window.handle, GLFW_KEY_D) == GLFW_PRESS)
      player.position[0] += speed;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    object_draw(&player);
    object_draw(&ground);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  texture_delete(&global.texture.player);
  texture_delete(&global.texture.white);
  quad_delete();
  window_close();

  return 0;
}
