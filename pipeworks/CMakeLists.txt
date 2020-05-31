
if(NOT MSVC)
add_compile_options(-g -O3 -Wno-incompatible-pointer-types)
endif()

if(NOT DEFINED PW_BUILD_SHARED)
set(PW_BUILD_SHARED ON)
endif()

if(NOT DEFINED PW_BUILD_STATIC)
set(PW_BUILD_STATIC ON)
endif()

if(NOT PW_BUILD_SHARED AND NOT PW_BUILD_STATIC)
message(FATAL_ERROR "libpipeworks Error: Not building either pipeworks shared or pipeworks static")
endif()


add_library(pipeworks-objects OBJECT src/engine.c src/thing.c src/game.c src/ll.c ../include/pipeworks/engine.h ../include/pipeworks/game.h ../include/pipeworks/thing.h ../include/pipeworks/pw-std.h)

if(PW_BUILD_SHARED)
message(STATUS "libpipeworks: Building Pipeworks Shared Library")
add_library(pipeworks-shared SHARED $<TARGET_OBJECTS:pipeworks-objects>)
target_link_libraries(pipeworks-shared SDL2 png FLAC)
set_target_properties(pipeworks-shared PROPERTIES OUTPUT_NAME "pipeworks")
set_target_properties(pipeworks-shared PROPERTIES SOVERSION 0)
set_property(TARGET pipeworks-shared PROPERTY C_STANDARD 11)
install(TARGETS pipeworks-shared
    EXPORT pipeworks
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
add_library(pipeworks ALIAS pipeworks-shared)
endif()
if(PW_BUILD_STATIC)
message(STATUS "libpipeworks: Building Pipeworks Static Library")
add_library(pipeworks-static STATIC $<TARGET_OBJECTS:pipeworks-objects>)
if(NOT WIN32)
set_target_properties(pipeworks-static PROPERTIES OUTPUT_NAME "pipeworks")
else()
set_target_properties(pipeworks-static PROPERTIES OUTPUT_NAME "pipeworks_static")
endif()
target_link_libraries(pipeworks-static SDL2 png FLAC)
set_property(TARGET pipeworks-static PROPERTY C_STANDARD 11)
install(TARGETS pipeworks-static
    EXPORT pipeworks
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
if(NOT PW_BUILD_SHARED)
add_library(pipeworks ALIAS pipeworks-static)
endif()
endif()


install(EXPORT pipeworks
    NAMESPACE pipeworks::
    DESTINATION lib/cmake/pipeworks)
