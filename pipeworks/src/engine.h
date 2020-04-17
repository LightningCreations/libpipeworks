#ifndef PRIVATE_ENGINE_H
#define PRIVATE_ENGINE_H

#include <pipeworks/engine.h>
#include "ll.h"
#include <SDL.h>

struct pw_engine {
    ll *things; // list of (pw_thing *)
    SDL_Thread *thread;
};

#endif
