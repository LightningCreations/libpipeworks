#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pipeworks/render_interface.h>

#include "../stb_image.h"
#include "../pw_util.h"

#include "sprite.h"

static void pw_update_sprite(pw_engine *engine, pw_thing *thing) {
}

static void pw_render_sprite(pw_engine *engine, pw_thing *thing, pw_render_interface render) {
    pw_sprite *sprite = (pw_sprite*) thing;
    uint32_t frameWidth = sprite->frameWidth;
    uint32_t frameHeight = sprite->frameHeight;
    float widthf = sprite->width;
    float heightf = sprite->height;
    uint32_t width = (uint32_t) floor(widthf);
    uint32_t height = (uint32_t) floor(heightf);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            pw_ri_plot_pixel(render, i, j, 0xffffff);
        }
    }
}

static void pw_sprite_load_frame(pw_sprite *sprite, uint32_t index, const char *rel_name) {
    char *name = pw_get_absolute_path(rel_name);

    int width, height, num_components;
    unsigned char *image_data = stbi_load(name, &width, &height, &num_components, 4); // Force 4 bytes per pixel

    // And now, to convert to our own format

    if(
        ((sprite->frameWidth != 0) && (sprite->frameWidth != width)) ||
        ((sprite->frameHeight != 0) && (sprite->frameHeight != height))
    ) {
        printf("libpipeworks error: multiple frames of the same sprite are not the same size!\n");
        printf("No sane way to continue, exiting.\n");
        exit(1);
    }
    sprite->frameWidth = width;
    sprite->frameHeight = height;

    sprite->frames[index] = malloc(width * height * sizeof(uint32_t));
    uint32_t(*frame)[height] = sprite->frames[index];

    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
            frame[x][y] = // 0xAARRGGBB
                (image_data[(y*width+x)*4+0] << 16) | // R
                (image_data[(y*width+x)*4+1] <<  8) | // G
                (image_data[(y*width+x)*4+2] <<  0) | // B
                (image_data[(y*width+x)*4+3] << 24)   // A
            ;

    stbi_image_free(image_data);
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
