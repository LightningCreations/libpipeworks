#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../pw_util.h"

#include "sprite.h"

static void pw_update_sprite(pw_engine *engine, pw_thing *thing) {
}

static void pw_render_sprite(pw_engine *engine, pw_thing *thing) {
}

static void pw_sprite_load_frame(pw_sprite *sprite, uint32_t index, const char *rel_name) {
    char *name = pw_get_absolute_path(rel_name);

    // WIP
}

pw_sprite* pw_init_sprite(float x, float y, float width, float height, float depth, uint32_t numFrames, const char **frames) {
    pw_sprite *result = malloc(sizeof(pw_sprite));
    result->x = x;
    result->y = y;
    result->width = width;
    result->height = height;
    result->thing.depth = depth;
    result->thing.update = pw_update_sprite;
    result->thing.render = pw_render_sprite;
    result->numFrames = numFrames;
    result->frameWidth = 0;  // Set by loading functions
    result->frameHeight = 0; // Set by loading functions
    result->frames = malloc(sizeof(result->frames[0])*numFrames);
    for(uint32_t i = 0; i < numFrames; i++) {
        pw_sprite_load_frame(result, i, frames[i]);
    }

    return result;
}
