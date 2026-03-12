#include <engine/graphics/window.h>
#include <engine/model/camera.h>

GLFWwindow *window_handle;
int window_width;
int window_height;
vec2 mouse_world_pos;
vec2 mouse_screen_pos;
mat4x4 window_projection;

static void mouse_move_callback(GLFWwindow *window, double xpos, double ypos)
{
  mouse_screen_pos[0] = (float)xpos;
  mouse_screen_pos[1] = (float)ypos;

  float flipped_y = (float)window_height - (float)ypos;
  mouse_world_pos[0] = (float)xpos + camera_pos[0] - window_width * 0.5f;
  mouse_world_pos[1] = flipped_y + camera_pos[1] - window_height * 0.5f;
}

static void window_resize_callback(GLFWwindow *window, int width, int height)
{
  window_width = width;
  window_height = height;

  mat4x4_ortho(window_projection, 0.0f, width, 0.0f, height, -1.0f, 1.0f);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
}

void window_init(int width, int height, const char *title)
{
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_handle = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window_handle) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window_handle);
  glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glfwSetCursorPosCallback(window_handle, mouse_move_callback);
  glfwSetFramebufferSizeCallback(window_handle, window_resize_callback);
  glfwSetMouseButtonCallback(window_handle, mouse_button_callback);

  window_resize_callback(window_handle, width, height);
}

void window_cleanup(void)
{
  if (window_handle)
    glfwDestroyWindow(window_handle);

  glfwTerminate();
}
