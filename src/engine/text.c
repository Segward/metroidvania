#include <engine/text.h>
#include <engine/vertex.h>
#include <engine/shader.h>
#include <engine/global.h>
#include <stdio.h>
#include <string.h>
#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct glyph
{
  GLuint texture;
  int width;
  int height;
  int bearing_x;
  int bearing_y;
  unsigned advance;
} glyph_t;

static glyph_t glyphs[128];

static GLuint vao;
static GLuint vbo;
static GLuint program;

static void upload_glyph_quad(float verts[6][4])
{
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 6 * 4, verts);
}

static void make_1x1_empty_red_texture(void)
{
  unsigned char empty = 0;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 1, 1, 0, GL_RED, GL_UNSIGNED_BYTE, &empty);
}

static bool load_font_ascii(const char* font_path, int pixel_height)
{
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    fprintf(stderr, "ERROR::FREETYPE: FT_Init_FreeType failed\n");
    return false;
  }

  FT_Face face;
  if (FT_New_Face(ft, font_path, 0, &face)) {
    fprintf(stderr, "ERROR::FREETYPE: FT_New_Face failed for '%s'\n", font_path);
    FT_Done_FreeType(ft);
    return false;
  }

  FT_Set_Pixel_Sizes(face, 0, (FT_UInt)pixel_height);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (unsigned char c = 0; c < 128; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      glyphs[c].texture = 0;
      glyphs[c].width = glyphs[c].height = 0;
      glyphs[c].bearing_x = glyphs[c].bearing_y = 0;
      glyphs[c].advance = 0;
      continue;
    }

    FT_GlyphSlot g = face->glyph;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    int w = (int)g->bitmap.width;
    int h = (int)g->bitmap.rows;

    if (w == 0 || h == 0) {
      make_1x1_empty_red_texture();
    } else {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
                   w, h, 0,
                   GL_RED, GL_UNSIGNED_BYTE,
                   g->bitmap.buffer);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glyphs[c].texture = tex;
    glyphs[c].width = w;
    glyphs[c].height = h;
    glyphs[c].bearing_x = (int)g->bitmap_left;
    glyphs[c].bearing_y = (int)g->bitmap_top;
    glyphs[c].advance = (unsigned int)g->advance.x;
  }

  glBindTexture(GL_TEXTURE_2D, 0);

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  return true;
}

bool text_init(void)
{
  program = shader_create("assets/text.vert", "assets/text.frag");
  if (!program)
    return false;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  if (!load_font_ascii("assets/arial.ttf", 48))
    return false;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return true;
}

static mat4x4 projection;

void text_draw(const char* str, vec2 position, float scale, vec4 color)
{
  if (!str || !str[0])
    return;

  mat4x4_ortho(projection, 0, global.window.width, 0, global.window.height, -1, 1);

  glUseProgram(program);
  shader_update_mat4x4(program, "uProj", projection);

  shader_update_vec4(program, "uColor", color);

  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(vao);

  float x = position[0];
  float y = position[1];

  for (const char* p = str; *p; p++) {
    unsigned char c = (unsigned char)*p;
    glyph_t g = glyphs[c];

    if (g.texture == 0) {
      x += 8.0f * scale;
      continue;
    }

    float xpos = x + (float)g.bearing_x * scale;
    float ypos = y - (float)(g.height - g.bearing_y) * scale;

    float w = (float)g.width * scale;
    float h = (float)g.height * scale;

    float verts[6][4] = {
      { xpos,     ypos + h, 0.0f, 0.0f },
      { xpos,     ypos,     0.0f, 1.0f },
      { xpos + w, ypos,     1.0f, 1.0f },

      { xpos,     ypos + h, 0.0f, 0.0f },
      { xpos + w, ypos,     1.0f, 1.0f },
      { xpos + w, ypos + h, 1.0f, 0.0f }
    };

    shader_update_texture(program, "uTexture", g.texture);

    upload_glyph_quad(verts);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    x += (float)(g.advance >> 6) * scale;
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
