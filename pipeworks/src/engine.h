#ifndef PRIVATE_ENGINE_H
#define PRIVATE_ENGINE_H

#include <pipeworks/engine.h>
#include "stretchy_buffer.h"

struct pw_engine_state {
    pw_thing **things; // STRETCHY BUFFER, vector of (pw_thing *)
} pw_engine_state;

#endif
