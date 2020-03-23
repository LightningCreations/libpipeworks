#include <pipeworks/engine.h>

#define STATE_MENU STATE_PRIME+1 // STATE_PRIME is the base of all non-reserved states

struct game_data
{
    pw_engine *engine;
    pw_thing *menu;
} game_data;

void game_load_state(pw_game_state next)
{
    pw_engine *engine = game_data.engine;
    switch(next)
    {
    case STATE_PRIME:
        pw_load_state(engine, STATE_MENU);
        break;
    case STATE_MENU:
        if(!game_data.menu) game_data.menu = pw_init_thing();
        pw_engine_add_thing(engine, game_data.menu);
        break;
    default:
        pw_load_state(engine, STATE_PRIME); // RESET
        break;
    }
}

int main()
{
    pw_engine *engine = pw_init_engine();
    game_data.engine = engine;

    pw_game *game = pw_init_game();

    pw_set_load_state(game, game_load_state);

    pw_set_game(engine, game);
}
