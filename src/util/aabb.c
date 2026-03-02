#include <util/aabb.h>

static inline float f_abs(float x) { return x < 0.0f ? -x : x; }
static inline float f_sign(float x) { return (x < 0.0f) ? -1.0f : 1.0f; }

void aabb_collide_and_correct(vec2 posA, vec2 sizeA, vec2 posB, vec2 sizeB)
{
    // Assumes:
    // pos = center
    // size = (width, height)

    const float ahx = sizeA[0] * 0.5f;
    const float ahy = sizeA[1] * 0.5f;
    const float bhx = sizeB[0] * 0.5f;
    const float bhy = sizeB[1] * 0.5f;

    const float dx = posB[0] - posA[0];
    const float px = (ahx + bhx) - f_abs(dx);
    if (px <= 0.0f) return;

    const float dy = posB[1] - posA[1];
    const float py = (ahy + bhy) - f_abs(dy);
    if (py <= 0.0f) return;

    // Separate along the axis with the least penetration
    if (px < py) {
        posA[0] -= px * f_sign(dx);
    } else {
        posA[1] -= py * f_sign(dy);
    }
}
