#ifndef PIPEWORKS_GAME_H
#define PIPEWORKS_GAME_H
// Libc includes
#include <stdint.h>

// GAME STATE
typedef uint8_t pw_game_state;
enum{STATE_PRIME=2};

// GAME
typedef struct pw_game pw_game;


#include <pipeworks/engine.h>

#ifdef __cplusplus
extern"C"{
#endif

// Creation/destruction
pw_game *pw_init_game();

void pw_destroy_game(pw_game *);

// Configuration
void pw_set_load_state(pw_game *, void(*)(pw_game_state, pw_engine *, void *), void *);

#ifdef __cplusplus
};
#endif

#endif
