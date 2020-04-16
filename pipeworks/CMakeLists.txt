include(FindThreads)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wno-incompatible-pointer-types")

add_library(pipeworks src/engine.c src/thing.c src/game.c src/ll.c ../include/pipeworks/engine.h ../include/pipeworks/game.h ../include/pipeworks/thing.h ../include/pipeworks/pw-std.h)

add_dependencies(pipeworks SDL2 png FLAC)
target_link_libraries(pipeworks SDL2 png FLAC)
install(TARGETS pipeworks
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
