#include <pipeworks/engine.h>
#include "engine.h"

void init_engine() {
    pw_engine_state.things = NULL; // STRETCHY BUFFER
}

void add_thing(pw_thing *thing) {
    sb_push(pw_engine_state.things, thing);
}
