#ifndef SPRITE_H
#define SPRITE_H

#include <pch.h>
#include <util/animation.h>

typedef struct sprite
{
  vec2 position;
  vec2 size;
  GLuint texture;
  animation_t *animation;
  bool animated;
} sprite_t;

void sprite_create(sprite_t *sprite, GLuint texture);
void sprite_apply_animation(sprite_t *sprite, animation_t *animation);
void sprite_update(sprite_t *sprite, vec2 position, vec2 size);
void sprite_draw(sprite_t *sprite);

#endif
