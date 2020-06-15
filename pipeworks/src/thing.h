#include <pipeworks/engine.h>
#include <pipeworks/thing.h>

struct pw_thing {
    void(*update)(pw_engine *engine);
    void(*render)(pw_engine *engine);
};
