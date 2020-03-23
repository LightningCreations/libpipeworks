#ifndef PIPEWORKS_GAME_H
#define PIPEWORKS_GAME_H

// Libc includes
#include <stdint.h>

// GAME STATE
typedef uint_fast8_t pw_game_state;
#define STATE_PRIME 2 // Reserve 0 and 1 for internal use

// GAME
typedef struct pw_game pw_game;

// Creation/destruction
pw_game* pw_init_game();
void pw_destroy_game(pw_game*);

// Configuration
void pw_set_load_state(pw_game*, void(*)(pw_game_state));

#endif
