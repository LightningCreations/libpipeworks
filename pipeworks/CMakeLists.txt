
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wno-incompatible-pointer-types")

add_library(pipeworks src/engine.c src/thing.c src/game.c src/ll.c)

target_link_libraries(pipeworks SDL png flac)
install(TARGETS pipeworks)

