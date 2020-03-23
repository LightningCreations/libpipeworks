set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wno-incompatible-pointer-types")

add_library(pipeworks SHARED src/engine.c src/thing.c src/game.c src/ll.c)
