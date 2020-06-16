#include "game.h"
#include <pipeworks/game.h>

#include <stdlib.h>

#include <pipeworks/engine.h>

pw_game* pw_init_game()
{
    pw_game *result = malloc(sizeof(pw_game));
    result->load_state = NULL;
    result->load_state_userdata = NULL;
    result->load_state_dtor = NULL;
    return result;
}

void pw_set_load_state(pw_game *game, void(*load_state)(pw_game_state, pw_engine*, void*), void *userdata)
{
    pw_set_load_state_cleanup(game,load_state,userdata,NULL);
}

void pw_set_load_state_cleanup(pw_game *game, void(*load_state)(pw_game_state, pw_engine *, void *), void *userdata,void(*dtor)(void *)){
    if(game->load_state_userdata&&game->load_state_dtor)
        game->load_state_dtor(game->load_state_userdata);
    game->load_state = load_state;
    game->load_state_userdata = userdata;
    game->load_state_dtor = dtor;
}