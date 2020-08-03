#include <png.h>
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

static bool pw_sprite_load_frame_png(pw_sprite *sprite, uint32_t index, const char *name) {
    FILE *png = fopen(name, "rb");
    if(!png) return 0;
    uint8_t header[8];
    fread(header, 1, 8, png);
    if(png_sig_cmp(header, 0, 8)) {
        fclose(png);
        return 0;
    }
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, printf, printf);
    if(!png_ptr) {
        fclose(png);
        return 0;
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr) {
        fclose(png);
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        return 0;
    }
    png_infop end_info = png_create_info_struct(png_ptr);
    if(!end_info) {
        fclose(png);
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        return 0;
    }
    if(setjmp(png_jmpbuf(png_ptr))) { // AAAA setjmp (this may kill Windows; we'll see)
        fclose(png);
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return 0;
    }
    png_init_io(png_ptr, png);
    png_set_sig_bytes(png_ptr, 8);
    
    return 1;
}

static void pw_sprite_load_frame(pw_sprite *sprite, uint32_t index, const char *rel_name) {
    char *name = pw_get_absolute_path(rel_name);

    size_t name_len = strlen(name);
    if(name_len >= 4 && name[name_len-4] == '.' && name[name_len-3] == 'p' && name[name_len-2] == 'n' && name[name_len-1] == 'g'
        && pw_sprite_load_frame_png(sprite, index, name)) return;
    else {
        printf("Couldn't load image data!\n");
    }
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
