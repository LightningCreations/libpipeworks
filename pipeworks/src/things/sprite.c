#include <stdlib.h>
#include "sprite.h"

pw_sprite* pw_init_sprite(float x, float y, float width, float height, float depth, uint32_t numFrames, const char *const *const frames) {
    pw_sprite *result = malloc(sizeof(pw_sprite));
    result->x = x;
    result->y = y;
    result->width = width;
    result->height = height;
    result->thing.depth = depth;

    return result;
}
