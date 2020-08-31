#ifndef PW_RENDER_INTERFACE_H
#define PW_RENDER_INTERFACE_H

typedef struct pw_render_interface pw_render_interface;
typedef struct pw_render_interface_vtable pw_render_interface_vtable;

#include <stdint.h>
#include <stdlib.h>

struct pw_render_interface_vtable { // Based on Rust Pre-RFC 12598 for stable vtables
    size_t size;
    size_t align;
    void(*destroy)(void *data);
    void(*dealloc)(void *data, size_t size);
    void(*plot_pixel)(void *data, uint32_t x, uint32_t y, uint32_t color);
    void *unused1; // Avoids major versions
    void *unused2;
    void *unused3;
    void *unused4;
    void *unused5;
    void *unused6;
    void *unused7;
};

struct pw_render_interface {
    pw_render_interface_vtable *vtable;
    void *data;
};

#endif
