include(FindOpenMP)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wno-incompatible-pointer-types ${OpenMP_C_FLAGS}")

add_library(pipeworks src/engine.c src/thing.c src/game.c src/ll.c)

add_dependencies(pipeworks SDL2 png FLAC)
target_link_libraries(pipeworks SDL2 png FLAC)
install(TARGETS pipeworks)

