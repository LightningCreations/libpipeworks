#include <stdint.h>

#include <pipeworks/things/sprite.h>
#include "../thing.h" // Include private header; we're doing private things

struct pw_sprite {
    struct pw_thing thing;
    float x;
    float y;
    float width;
    float height;
};
