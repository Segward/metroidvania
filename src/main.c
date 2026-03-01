#include <util/global.h>
#include <util/time.h>
#include <util/animation.h>

#include <graphics/window.h>
#include <graphics/texture.h>

#include <shapes/quad.h>
#include <shapes/text.h>

#include <model/sprite.h>

static sprite_t sprite;

static animation_t front;
static animation_t back;
static animation_t left;
static animation_t right;

static vec2 position;

static double time = 0;

int main(void) 
{
  if (!window_init(800, 800, "metroidvania"))
    goto cleanup;

  if (!quad_init())
    goto cleanup;

  if (!text_init())
    goto cleanup;

  if (!texture_init())
    goto cleanup;

  time_init();

  animation_create(&front, 4, 4);
  animation_frame(&front, 0, 0);
  animation_frame(&front, 1, 0);
  animation_frame(&front, 2, 0);
  animation_frame(&front, 3, 0);

  animation_create(&back, 4, 4);
  animation_frame(&back, 0, 3);
  animation_frame(&back, 1, 3);
  animation_frame(&back, 2, 3);
  animation_frame(&back, 3, 3);

  animation_create(&left, 4, 4);
  animation_frame(&left, 0, 1);
  animation_frame(&left, 1, 1);
  animation_frame(&left, 2, 1);
  animation_frame(&left, 3, 1);

  animation_create(&right, 4, 4);
  animation_frame(&right, 0, 2);
  animation_frame(&right, 1, 2);
  animation_frame(&right, 2, 2);
  animation_frame(&right, 3, 2);

  sprite_create(&sprite, global.texture.sprite);
  sprite_apply_animation(&sprite, &front);

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();

    float speed = global.time.delta_time * 200;

    if (glfwGetKey(global.window.handle, GLFW_KEY_W) == GLFW_PRESS)
    {
      sprite_apply_animation(&sprite, &back);
      vec2_add(sprite.position, sprite.position, (vec2){ 0.0f, speed});
    }

    if (glfwGetKey(global.window.handle, GLFW_KEY_A) == GLFW_PRESS)
    {
      sprite_apply_animation(&sprite, &left);
      vec2_add(sprite.position, sprite.position, (vec2){ -speed, 0.0f});
    }

    if (glfwGetKey(global.window.handle, GLFW_KEY_S) == GLFW_PRESS)
    {
      sprite_apply_animation(&sprite, &front);
      vec2_add(sprite.position, sprite.position, (vec2){ 0.0f, -speed});
    }

    if (glfwGetKey(global.window.handle, GLFW_KEY_D) == GLFW_PRESS)
    {
      sprite_apply_animation(&sprite, &right);
      vec2_add(sprite.position, sprite.position, (vec2){ speed, 0.0f});
    }

    time += global.time.delta_time;
    if (time >= 0.5)
    {
      sprite_update(&sprite, sprite.position, sprite.size);
      time = 0;
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sprite_draw(&sprite);

    text_draw("Hello player!", 
              (vec2){ 500.0f, 600.0f }, 0.5f, 
              (vec4){1.0f, 1.0f, 1.0f, 1.0f});

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

cleanup:

  animation_delete(&front);
  animation_delete(&back);
  animation_delete(&left);
  animation_delete(&right);

  texture_cleanup();
  text_delete();
  quad_delete();
  window_close();

  return 0;
}
