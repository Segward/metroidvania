#include <engine/global.h>
#include <engine/render.h>
#include <engine/quad.h>
#include <cglm/cglm.h>

static float speed = 1.0f;
static vec3 pos;

void handle_input(float dt) {
  vec3 dir = { 0.0f, 0.0f, 0.0f };
  if (glfwGetKey(global.window.handle, GLFW_KEY_W) == GLFW_PRESS)
    dir[1] += 1.0f;
  if (glfwGetKey(global.window.handle, GLFW_KEY_S) == GLFW_PRESS) 
    dir[1] -= 1.0f;
  if (glfwGetKey(global.window.handle, GLFW_KEY_A) == GLFW_PRESS) 
    dir[0] -= 1.0f;
  if (glfwGetKey(global.window.handle, GLFW_KEY_D) == GLFW_PRESS) 
    dir[0] += 1.0f;

  if (dir[0] == 0.0f && dir[1] == 0.0f)
    return;

  glm_vec3_normalize(dir);
  glm_vec3_muladds(dir, speed * dt, pos);
}

int main() {
  render_init();
  double last = glfwGetTime();

  while (!glfwWindowShouldClose(global.window.handle)) {
    double now = glfwGetTime();
    float dt = (float)(now - last);
    last = now;

    handle_input(dt);
    render_begin();
    quad_draw(pos, (vec2){0.25f, 0.25f}, (vec4){0.0f, 1.0f, 0.0f, 1.0f});
    render_end();
  }

  return 0;
}
