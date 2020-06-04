#ifndef PIPEWORKS_THING_H_2020_04_17_14_40
#define PIPEWORKS_THING_H_2020_04_17_14_40
#ifdef __cplusplus
extern"C"{
#endif

#include <pipeworks/config.h>

typedef struct pw_thing pw_thing;

PIPEWORKS_API pw_thing *pw_init_thing();

PIPEWORKS_API void pw_destroy_thing(pw_thing *);

#ifdef __cplusplus
};
#endif
#endif
