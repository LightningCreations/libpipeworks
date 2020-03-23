// Engine includes
#include <pipeworks/engine.h>
#include "engine.h"

// Libc includes
#include <stdlib.h>

// External lib includes
#include "stretchy_buffer.h"

// Pipeworks includes
#include <pipeworks/thing.h>

pw_engine* pw_init_engine()
{
    pw_engine *result = malloc(sizeof(pw_engine));
    result->things = NULL; // STRETCHY BUFFER
    return result;
}

void pw_engine_add_thing(pw_engine *engine, pw_thing *thing)
{
    sb_push(engine->things, thing);
}

void pw_destroy_engine(pw_engine *engine)
{
    if(!engine) return;
    for(int i = 0; i < sb_count(engine->things); i++)
        pw_destroy_thing(engine->things[i]);
    sb_free(engine->things);
    free(engine);
}
