#ifndef PW_THINGS_SPRITE_H
#define PW_THINGS_SPRITE_H

#include "../pw-std.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pw_sprite pw_sprite;

PIPEWORKS_API pw_sprite* pw_init_sprite(float x, float y, float width, float height, float depth, uint32_t numFrames, const char *const *const frames); // All the consts

PIPEWORKS_API void pw_sprite_add_update_handler(void(*handler)(pw_sprite *sprite));

PIPEWORKS_API void pw_sprite_set_x(float x);
PIPEWORKS_API void pw_sprite_set_y(float y);
PIPEWORKS_API float pw_sprite_get_x();
PIPEWORKS_API float pw_sprite_get_y();
PIPEWORKS_API void pw_sprite_set_pos(float x, float y);

PIPEWORKS_API void pw_sprite_set_width(float width);
PIPEWORKS_API void pw_sprite_set_height(float height);
PIPEWORKS_API float pw_sprite_get_width();
PIPEWORKS_API float pw_sprite_get_height();
PIPEWORKS_API void pw_sprite_set_size(float width, float height);

PIPEWORKS_API void pw_sprite_set_pos_and_size(float x, float y, float width, float height);

PIPEWORKS_API void pw_sprite_set_frame(uint32_t id);

#ifdef __cplusplus
}
#endif

#endif
