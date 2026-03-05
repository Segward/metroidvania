#include <global.h>
#include <util/time.h>
#include <model/object.h>

#include <graphics/gl.h>
#include <graphics/win.h>
#include <graphics/quad.h>
#include <graphics/iquad.h>
#include <graphics/tex.h>

static object_t player;

int main(void) 
{
  win_init();
  gl_init();
  quad_init();
  iquad_init();

  tex_create(&global.texture.player, "assets/textures/player.png");
  tex_create(&global.texture.grass, "assets/textures/grass.jpg");
  vec4_dup(global.tint, (vec4){ 1.0f, 1.0f, 1.0f, 1.0f });

  object_create(&player, global.texture.player);

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();

    float halfW = global.window.width  * 0.5f;
    float halfH = global.window.height * 0.5f;

    float playerCenterX = player.pos[0] + player.size[0] * 0.5f;
    float playerCenterY = player.pos[1] + player.size[1] * 0.5f;

    mat4x4_identity(global.view);
    mat4x4_translate(global.view, -playerCenterX + halfW, -playerCenterY + halfH, 0.0f);

    float speed = global.time.delta_time * 200;
    if (glfwGetKey(global.window.handle, GLFW_KEY_W) == GLFW_PRESS)
      player.pos[1] += speed;

    if (glfwGetKey(global.window.handle, GLFW_KEY_A) == GLFW_PRESS)
      player.pos[0] -= speed;

    if (glfwGetKey(global.window.handle, GLFW_KEY_S) == GLFW_PRESS)
      player.pos[1] -= speed;

    if (glfwGetKey(global.window.handle, GLFW_KEY_D) == GLFW_PRESS)
      player.pos[0] += speed;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    object_draw(&player);

    vec2 offsets[16] = {
      {   0.0f,   0.0f }, {  60.0f,   0.0f }, { 120.0f,   0.0f }, { 180.0f,   0.0f },
      {   0.0f,  60.0f }, {  60.0f,  60.0f }, { 120.0f,  60.0f }, { 180.0f,  60.0f },
      {   0.0f, 120.0f }, {  60.0f, 120.0f }, { 120.0f, 120.0f }, { 180.0f, 120.0f },
      {   0.0f, 180.0f }, {  60.0f, 180.0f }, { 120.0f, 180.0f }, { 180.0f, 180.0f }
    };

    iquad_draw(offsets, 16, (vec2){ 50.0f, 50.0f }, 
               (vec4){ 1.0f, 1.0f, 1.0f, 1.0f }, global.texture.grass);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  glDeleteTextures(1, &global.texture.grass);
  glDeleteTextures(1, &global.texture.player);

  iquad_cleanup();
  quad_cleanup();
  win_cleanup();

  return 0;
}
