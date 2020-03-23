// Thing includes
#include <pipeworks/thing.h>

// libc includes
#include <stdlib.h>

pw_thing* pw_init_thing()
{
    return NULL;
}

void pw_destroy_thing(pw_thing *thing)
{
    if(!thing) return;
    free(thing);
}
