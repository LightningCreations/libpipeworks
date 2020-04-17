// Engine includes
#include <pipeworks/engine.h>
#include "engine.h"

// Libc includes
#include <stdlib.h>

// Non-pipeworks lib includes
#include "ll.h"
#include <SDL.h>

// Pipeworks includes
#include <pipeworks/thing.h>

volatile uint8_t pw_activeEngines;

pw_engine* pw_init_engine()
{
    pw_engine *result = malloc(sizeof(pw_engine));
    result->things = ll_init();
    return result;
}

void pw_internal_start0(void *_engine)
{
    pw_engine *engine = (pw_engine*) _engine;

    pw_activeEngines++;
    if(pw_activeEngines == 1) // TODO: Improve thread safety
    {
        SDL_Init(SDL_INIT_VIDEO);
    }
    SDL_Window *window = SDL_CreateWindow("TODO: Add config for window name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);

    SDL_Delay(3000); // TODO: Add game loop

    SDL_DestroyWindow(window);

    pw_activeEngines--;
    if(pw_activeEngines == 0)
    {
        SDL_Quit();
    }
}

void pw_start(pw_engine *engine)
{
    engine->thread = SDL_CreateThread(pw_internal_start0, "Pipeworks Engine Thread", engine);
}

void pw_join(pw_engine *engine)
{
    SDL_WaitThread(engine->thread, NULL);
}

void pw_engine_add_thing(pw_engine *engine, pw_thing *thing)
{
    ll_push(engine->things, thing);
}

void pw_load_state(pw_engine *engine, pw_game_state next)
{
}

void pw_set_game(pw_engine *engine, pw_game *game)
{
}

void pw_destroy_engine(pw_engine *engine)
{
    if(!engine) return;
    ll_foreach(engine->things, pw_destroy_thing);
    ll_free(engine->things);
    free(engine);
}
