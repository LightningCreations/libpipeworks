#ifndef PRIVATE_GAME_H
#define PRIVATE_GAME_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <pipeworks/game.h>

#include <pipeworks/engine.h>

struct pw_game
{
    void(*load_state)(pw_game_state, pw_engine*, void*);
    void *load_state_userdata;
};

#ifdef __cplusplus
}
#endif

#endif
