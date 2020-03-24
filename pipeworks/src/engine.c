// Engine includes
#include <pipeworks/engine.h>
#include "engine.h"

// Libc includes
#include <stdlib.h>

// Non-pipeworks lib includes
#include "ll.h"

// Pipeworks includes
#include <pipeworks/thing.h>

pw_engine* pw_init_engine()
{
    pw_engine *result = malloc(sizeof(pw_engine));
    result->things = ll_init();
    return result;
}

void pw_engine_add_thing(pw_engine *engine, pw_thing *thing)
{
    ll_push(engine->things, thing);
}

void pw_load_state(pw_engine *engine, pw_game_state next)
{
}

void pw_set_game(pw_engine *engine, pw_game *game)
{
}

void pw_destroy_engine(pw_engine *engine)
{
    if(!engine) return;
    ll_foreach(engine->things, pw_destroy_thing);
    ll_free(engine->things);
    free(engine);
}
