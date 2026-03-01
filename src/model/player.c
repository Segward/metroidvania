#include <model/player.h>
#include <model/sprite.h>
#include <util/animation.h>
#include <util/global.h>

static sprite_t sprite;

static animation_t front;
static animation_t back;
static animation_t left;
static animation_t right;

static double time = 0;

void player_init(void)
{
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
}

void player_update(void)
{
  time += global.time.delta_time;
  if (time < 0.5)
    return;

  sprite_update(&sprite, sprite.position, sprite.size);
  time = 0;
}

void player_draw(void)
{
  sprite_draw(&sprite);
}

void player_cleanup(void)
{
  animation_delete(&front);
  animation_delete(&back);
  animation_delete(&left);
  animation_delete(&right);
}
