#include <global.h>
#include <util/time.h>

#include <graphics/gl.h>
#include <graphics/win.h>
#include <graphics/quad.h>
#include <graphics/tex.h>

static inline float frand(float a, float b)
{
  return a + (b - a) * ((float)rand() / (float)RAND_MAX);
}

#define PARTICLE_COUNT 1000000

int main(void) 
{
  win_init();
  gl_init();
  quad_init();

  mat4x4_identity(global.view);
  tex_create(&global.texture.player, "assets/textures/player.png");
  tex_create(&global.texture.grass, "assets/textures/grass.jpg");
  tex_white(&global.texture.white);
  vec4_dup(global.tint, (vec4){ 1.0f, 1.0f, 1.0f, 1.0f });

  quad_t *particles = malloc((size_t)PARTICLE_COUNT * sizeof(*particles));
  assert(particles);

  for (int i = 0; i < PARTICLE_COUNT; i++)
  {
    particles[i].offset[0] = frand(0.0f, global.window.width);
    particles[i].offset[1] = frand(0.0f, global.window.height);

    float s = frand(1.0f, 2.0f);
    particles[i].size[0] = s;
    particles[i].size[1] = s;

    float a = frand(0.5f, 1.0f);
    particles[i].color[0] = 1.0f;
    particles[i].color[1] = 1.0f;
    particles[i].color[2] = 1.0f;
    particles[i].color[3] = a;
  }

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();

    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
      float speed = 20.0f + (1.0f - particles[i].color[3]) * 60.0f;
      particles[i].offset[1] -= speed * global.time.delta_time;

      if (particles[i].offset[1] < -particles[i].size[1])
      {
        particles[i].offset[1] = global.window.height + particles[i].size[1];
        particles[i].offset[0] = frand(0.0f, global.window.width);
      }
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    quad_draw(particles, global.texture.white, PARTICLE_COUNT);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
  }

  glDeleteTextures(1, &global.texture.grass);
  glDeleteTextures(1, &global.texture.player);

  quad_cleanup();
  win_cleanup();

  return 0;
}
