typedef struct pw_engine pw_engine;

#ifndef PIPEWORKS_ENGINE_H
#define PIPEWORKS_ENGINE_H

#include "game.h"
#include "thing.h"

// Creation/destruction
pw_engine* pw_init_engine();
void pw_destroy_engine(pw_engine*);

// Threading
void pw_start(pw_engine*);
void pw_join(pw_engine*);
void pw_stop(pw_engine*);

// Configuring
void pw_set_game(pw_engine*, pw_game*);

// Commands
void pw_engine_add_thing(pw_engine*, pw_thing*); // To distinguish from pw_canvas_add_thing
void pw_engine_clear_things(pw_engine*); // To distinguish from pw_canvas_clear_things
void pw_engine_remove_thing(pw_engine*, pw_thing*); // To distinguish from pw_canvas_remove_thing
void pw_load_state(pw_engine*, pw_game_state);

#endif
