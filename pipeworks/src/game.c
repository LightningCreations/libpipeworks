#include "game.h"
#include <pipeworks/game.h>

#include <stdlib.h>

#include <pipeworks/engine.h>

pw_game* pw_init_game()
{
    pw_game *result = malloc(sizeof(pw_game));
    return result;
}

void pw_set_load_state(pw_game *game, void(*load_state)(pw_game_state, pw_engine*, void*), void *userdata)
{
}
