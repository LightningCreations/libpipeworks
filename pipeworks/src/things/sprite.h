#include <stdint.h>

#include <pipeworks/things/sprite.h>
#include "../thing.h" // Include private header; we're doing private things

struct pw_sprite {
    struct pw_thing thing;
    float x;
    float y;
    float width;
    float height;
    uint32_t numFrames;
    uint16_t frameWidth;
    uint16_t frameHeight;
    uint32_t ***frames; // frames[id][x][y] (32-bit 0xAARRGGBB)
};
