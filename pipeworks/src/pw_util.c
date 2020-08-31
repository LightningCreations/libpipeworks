#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "whereami.c" // Include the C file; this is the only place we'll be using it, anyway.

static char *exepath;

char* pw_get_absolute_path(const char *path) {
    if(!exepath) {
        int dirname_len;
        int length = wai_getExecutablePath(NULL, 0, NULL);
        exepath = malloc(length+1);
        wai_getExecutablePath(exepath, length, &dirname_len);
        exepath[dirname_len+1] = 0; // Include the trailing slash
    }
    if(path[0] == '/') { // Path is already absolute
        char *abs_path = malloc(strlen(path)+1); // We have to make a copy in order to give a mutable, freeable string
        strcpy(abs_path, path);
        return abs_path;
    }
    char *abs_path = malloc(strlen(exepath)+strlen(path)+1);
    strcpy(abs_path, exepath);
    strcat(abs_path, path);
    return abs_path;
}
