// Thing includes
#include "thing.h"

// libc includes
#include <stdlib.h>

pw_thing* pw_init_thing()
{
    return malloc(sizeof(pw_thing));
}

void pw_destroy_thing(pw_thing *thing)
{
    if(!thing) return;
    free(thing);
}
