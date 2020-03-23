#include <stdlib.h>
#include "stretchy_buffer.h"

#include <pipeworks/engine.h>
#include "engine.h"

pw_engine* pw_init_engine() {
    pw_engine *result = malloc(sizeof(pw_engine));
    result->things = NULL; // STRETCHY BUFFER
    return result;
}

void pw_add_thing(pw_engine *engine, pw_thing *thing) {
    sb_push(engine->things, thing);
}
