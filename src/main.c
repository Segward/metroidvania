#include <engine/model/camera.h>
#include <engine/model/global.h>
#include <engine/model/input.h>
#include <engine/model/time.h>

#include <engine/graphics/window.h>
#include <engine/graphics/quad.h>
#include <engine/graphics/texture.h>

int main(void) 
{
  window_init(800, 800, "test");
  quad_init();
  time_init();

  GLuint tiles;
  texture_load_file(&tiles, "assets/textures/tiles.png");
  int width = 16;
  int height = 12;

  quad_t quads[2] = {0};

  float tile_w = 1.0f / width;
  float tile_h = 1.0f / height;

  quads[0].offset[0] = 0.0f;
  quads[0].offset[1] = 0.0f;

  quads[0].size[0] = 50.0f;
  quads[0].size[1] = 50.0f;

  quads[0].color[0] = 1.0f;
  quads[0].color[1] = 1.0f;
  quads[0].color[2] = 1.0f;
  quads[0].color[3] = 1.0f;

  quads[0].uv_offset[0] = 0 * tile_w;
  quads[0].uv_offset[1] = 0 * tile_h;

  quads[0].uv_size[0] = tile_w;
  quads[0].uv_size[1] = tile_h;

  quads[1].offset[0] = 50.0f;
  quads[1].offset[1] = 0.0f;

  quads[1].size[0] = 50.0f;
  quads[1].size[1] = 50.0f;

  quads[1].color[0] = 1.0f;
  quads[1].color[1] = 1.0f;
  quads[1].color[2] = 1.0f;
  quads[1].color[3] = 1.0f;

  quads[1].uv_offset[0] = 1 * tile_w;
  quads[1].uv_offset[1] = 0 * tile_h;

  quads[1].uv_size[0] = tile_w;
  quads[1].uv_size[1] = tile_h;

  while (!glfwWindowShouldClose(global.window.handle)) {
    time_update();
    camera_update((vec2){ 0.0f, 0.0f });

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    quad_draw(quads, tiles, 2);

    glfwSwapBuffers(global.window.handle);
    glfwPollEvents();
    input_update();
  }

  glDeleteTextures(1, &tiles);

  quad_cleanup();
  window_cleanup();

  return 0;
}
