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
    uint32_t(*get_min_x)(void *data);
    uint32_t(*get_max_x)(void *data);
    uint32_t(*get_min_y)(void *data);
    uint32_t(*get_max_y)(void *data);
    void *unused5;
    void *unused6;
    void *unused7;
    void *unused8;
    void *unused9;
    void *unused0;
    void *unused1;
};

struct pw_render_interface {
    pw_render_interface_vtable *vtable;
    void *data;
};

void pw_ri_plot_pixel(pw_render_interface render, uint32_t x, uint32_t y, uint32_t color);
uint32_t pw_ri_get_min_x(pw_render_interface render);
uint32_t pw_ri_get_max_x(pw_render_interface render);
uint32_t pw_ri_get_min_y(pw_render_interface render);
uint32_t pw_ri_get_max_y(pw_render_interface render);

#endif
