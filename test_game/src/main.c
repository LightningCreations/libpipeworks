#include <pipeworks/engine.h>
#include <pipeworks/things/sprite.h>

enum {
    STATE_MENU = STATE_PRIME+1
};

typedef struct data
{
    pw_engine *engine;
    pw_thing *menu;
} data;

void game_load_state(pw_game_state next, pw_engine *engine, void *_game_data)
{
    static const char *menu_gfx_list[1] = {"menu/menu.png"};
    data game_data = *((data*) _game_data);
    switch(next)
    {
    case STATE_PRIME:
        pw_load_state(engine, STATE_MENU);
        break;
    case STATE_MENU:
        if(!game_data.menu) game_data.menu = (pw_thing*) pw_init_sprite(0, 0, 0, 0, 0, 1, menu_gfx_list);
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

    pw_game *game = pw_init_game();

    data game_data;

    pw_set_load_state(game, game_load_state, (void*)(&game_data));

    pw_set_game(engine, game);

    pw_start(engine);
    pw_join(engine);

    pw_destroy_engine(engine);
}
