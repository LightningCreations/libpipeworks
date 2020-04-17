// Engine includes
#include <pipeworks/engine.h>
#include "engine.h"

// Libc includes
#include <stdio.h>
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
    int status = 1;
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
    if(!window)
    {
        printf("**PIPEWORKS ERROR** SDL failed to create a window: %s\n", SDL_GetError());
        goto cleanup; // Hey, there's one use case for a goto.
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        printf("**PIPEWORKS ERROR** SDL failed to create a renderer: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, 1280, 720);
    if(!texture) {
        printf("**PIPEWORKS ERROR** SDL failed to create a texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_Delay(3000); // TODO: MAIN LOOP

    status = 0;
    cleanup:
    if(texture) SDL_DestroyTexture(texture);
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    return status;
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
