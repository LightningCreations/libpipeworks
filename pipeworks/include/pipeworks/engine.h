#ifndef PIPEWORKS_ENGINE_H
#define PIPEWORKS_ENGINE_H
typedef struct pw_engine pw_engine;

#include <pipeworks/config.h>

#include <pipeworks/game.h>
#include <pipeworks/thing.h>

#ifdef __cplusplus
extern"C"{
#endif

// Creation/destruction
PIPEWORKS_API pw_engine *pw_init_engine();

PIPEWORKS_API void pw_destroy_engine(pw_engine *);

// Threading
PIPEWORKS_API void pw_start(pw_engine *);

PIPEWORKS_API void pw_join(pw_engine *);

PIPEWORKS_API void pw_stop(pw_engine *);

// Configuring
PIPEWORKS_API void pw_set_game(pw_engine *, pw_game *);

PIPEWORKS_API pw_game *pw_engine_release_game(pw_engine *);

// Commands
PIPEWORKS_API void pw_engine_add_thing(pw_engine *, pw_thing *); // To distinguish from pw_canvas_add_thing
PIPEWORKS_API void pw_engine_clear_things(pw_engine *); // To distinguish from pw_canvas_clear_things
PIPEWORKS_API void pw_engine_remove_thing(pw_engine *, pw_thing *); // To distinguish from pw_canvas_remove_thing
PIPEWORKS_API void pw_load_state(pw_engine *, pw_game_state);

#ifdef __cplusplus
};
#endif
#endif
