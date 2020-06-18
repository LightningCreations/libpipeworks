#ifndef PRIVATE_ENGINE_H
#define PRIVATE_ENGINE_H

#include <pipeworks/engine.h>
#include <pipeworks/game.h>
#include "ll.h"
#include <SDL2/SDL.h>

struct pw_engine {
    ll *things; // list of (pw_thing *)
    pw_game *game;
    SDL_Thread *thread;
    pw_bool trigger_load;
    pw_game_state next_state;
};

#endif
