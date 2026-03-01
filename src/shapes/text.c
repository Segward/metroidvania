#include <shapes/text.h>
#include <util/global.h>

#include <graphics/shader.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>

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

static bool load_font_ascii(const char* font_path, int pixel_height)
{
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) return false;

  FT_Face face;
  if (FT_New_Face(ft, font_path, 0, &face)) 
  {
    FT_Done_FreeType(ft);
    return false;
  }

  FT_Set_Pixel_Sizes(face, 0, (FT_UInt)pixel_height);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (unsigned char c = 0; c < 128; c++) 
  {
    glyphs[c] = (glyph_t){0};
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) continue;

    FT_GlyphSlot g = face->glyph;

    int w = (int)g->bitmap.width;
    int h = (int)g->bitmap.rows;

    glyphs[c].width     = w;
    glyphs[c].height    = h;
    glyphs[c].bearing_x = (int)g->bitmap_left;
    glyphs[c].bearing_y = (int)g->bitmap_top;
    glyphs[c].advance   = (unsigned)g->advance.x;

    if (w == 0 || h == 0) 
    {
      glyphs[c].texture = 0;
      continue;
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
                 w, h, 0,
                 GL_RED, GL_UNSIGNED_BYTE,
                 g->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glyphs[c].texture = tex;
  }

  glBindTexture(GL_TEXTURE_2D, 0);

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  return true;
}

bool text_init(void)
{
  if (!shader_create(&program, "assets/text.vert", "assets/text.frag"))
    return false;

  vertex_array_generate(&vao);
  vertex_buffer_generate(&vbo);

  vertex_array_bind(vao);
  vertex_buffer_dynamic(vbo, sizeof(float) * 6 * 4);
  vertex_array_attribute(0, 4, 4, 0);

  if (!load_font_ascii("assets/arial.ttf", 48)) 
  {
    text_delete();
    return false;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return true;
}

void text_delete(void)
{
  for (int i = 0; i < 128; i++) 
  {
    if (glyphs[i].texture) 
    {
      glDeleteTextures(1, &glyphs[i].texture);
      glyphs[i].texture = 0;
    }

    glyphs[i].width = glyphs[i].height = 0;
    glyphs[i].bearing_x = glyphs[i].bearing_y = 0;
    glyphs[i].advance = 0;
  }

  vertex_buffer_delete(&vbo);
  vertex_array_delete(&vao);
  shader_delete(program);
}

static mat4x4 projection;

void text_draw(const char* str, vec2 position, float scale, vec4 color)
{
  shader_use(program);
  shader_update_mat4x4(program, "uProj", global.window.projection);
  shader_update_vec4(program, "uColor", color);

  vertex_array_bind(vao);

  float x = position[0];
  float y = position[1];

  for (const char* p = str; *p; p++) {
    unsigned char c = (unsigned char)*p;
    const glyph_t g = glyphs[c];

    float advance_px = (float)(g.advance >> 6) * scale;

    if (!g.texture || g.width == 0 || g.height == 0) 
    {
      x += advance_px;
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
    vertex_buffer_subtitue(vbo, (GLfloat*)verts, sizeof(float) * 6 * 4, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    x += advance_px;
  }
}
