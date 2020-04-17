// Engine includes
#include <pipeworks/engine.h>
#include "engine.h"

// Libc includes
#include <stdlib.h>
#include <stdatomic.h>

// Non-pipeworks lib includes
#include "ll.h"
#include <SDL.h>
#include <SDL_thread.h>

// Pipeworks includes
#include <pipeworks/thing.h>



pw_engine* pw_init_engine()
{
    pw_engine *result = malloc(sizeof(pw_engine));
    result->things = ll_init();
    return result;
}

static void pw_internal_at_exit(void){
    SDL_Quit();
}

static int pw_internal_start0(void *_engine)
{
    static atomic_flag blocking = ATOMIC_FLAG_INIT;
    static atomic_flag init = ATOMIC_FLAG_INIT;
    init_critical_section: { // May be a good idea to hoist this to pw_init_engine()
        while(atomic_flag_test_and_set_explicit(&blocking,memory_order_acquire))/*yield*/;
        if(!atomic_flag_test_and_set(&init)&&SDL_Init(SDL_INIT_EVERYTHING))
            atomic_flag_clear(&init);
        else
            atexit(pw_internal_at_exit);
        atomic_flag_clear_explicit(&blocking,memory_order_release);
    }
    
    pw_engine *engine = (pw_engine*) _engine;

    SDL_Window *window = SDL_CreateWindow("TODO: Add config for window name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);

    SDL_Delay(3000); // TODO: Add game loop

    SDL_DestroyWindow(window);
    return 0;
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
