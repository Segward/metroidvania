#include <global.h>
#include <util/time.h>
#include <model/object.h>

#include <_graphics/_gl.h>
#include <_graphics/_win.h>
#include <_graphics/_quad.h>
#include <_graphics/_tex.h>

static object_t player;
static object_t ground;

int main(void) 
{
  win_init();
  gl_init();
  quad_init();

  tex_create(&global.texture.player, "assets/textures/player.png");
  tex_create(&global.texture.grass, "assets/textures/grass.jpg");

  object_create(&player, global.texture.player);
  vec2_dup(player.position, (vec2){ 400.0f, 400.0f });
  vec2_dup(player.size, (vec2){ 100.0f, 100.0f });

  object_create(&ground, global.texture.grass);
  vec2_dup(ground.position, (vec2){ 400.0f, 300.0f });
  vec2_dup(ground.size, (vec2){ 300.0f, 100.0f });

  vec4_dup(global.tint, (vec4){ 1.0f, 1.0f, 1.0f, 1.0f });

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();

    float halfW = global.window.width  * 0.5f;
    float halfH = global.window.height * 0.5f;

    float playerCenterX = player.position[0] + player.size[0] * 0.5f;
    float playerCenterY = player.position[1] + player.size[1] * 0.5f;

    mat4x4_identity(global.view);
    mat4x4_translate(global.view, -playerCenterX + halfW, -playerCenterY + halfH, 0.0f);

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

  glDeleteTextures(1, &global.texture.player);
  glDeleteTextures(1, &global.texture.grass);
  quad_cleanup();
  win_cleanup();

  return 0;
}
