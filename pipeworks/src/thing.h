#include <pipeworks/engine.h>
#include <pipeworks/thing.h>
#include <pipeworks/render_interface.h>

struct pw_thing {
    void(*update)(pw_engine *engine, pw_thing *me);
    void(*render)(pw_engine *engine, pw_thing *me, pw_render_interface renderer);
    float depth;
};
