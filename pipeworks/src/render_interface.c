#include <pipeworks/render_interface.h>

void pw_ri_plot_pixel(pw_render_interface render, uint32_t x, uint32_t y, uint32_t color) {
    render.vtable->plot_pixel(render.data, x, y, color);
}

uint32_t pw_ri_get_min_x(pw_render_interface render) {
    return render.vtable->get_min_x(render.data);
}

uint32_t pw_ri_get_max_x(pw_render_interface render) {
    return render.vtable->get_max_x(render.data);
}

uint32_t pw_ri_get_min_y(pw_render_interface render) {
    return render.vtable->get_min_y(render.data);
}

uint32_t pw_ri_get_max_y(pw_render_interface render) {
    return render.vtable->get_max_y(render.data);
}
