#ifndef PIPEWORKS_ENGINE_H
#define PIPEWORKS_ENGINE_H

#include "thing.h"

typedef struct pw_engine pw_engine;

pw_engine* pw_init_engine();
void add_thing(pw_engine*, pw_thing*);

#endif
