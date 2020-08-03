if(NOT DEFINED PW_BUILD_SHARED)
set(PW_BUILD_SHARED ON)
endif()

if(NOT DEFINED PW_BUILD_STATIC)
set(PW_BUILD_STATIC ON)
endif()

if(NOT PW_BUILD_SHARED AND NOT PW_BUILD_STATIC)
message(FATAL_ERROR "libpipeworks Error: Not building either pipeworks shared or pipeworks static")
endif()


add_library(pipeworks-objects OBJECT src/engine.c src/thing.c src/sort.c src/game.c src/ll.c src/things/sprite.c src/pw_util.c include/pipeworks/engine.h include/pipeworks/game.h include/pipeworks/thing.h include/pipeworks/pw-std.h include/pipeworks/things/sprite.h)

target_include_directories(pipeworks-objects PRIVATE include)
target_include_directories(pipeworks-objects PRIVATE ${PIPEWORKS_PNG_ROOTDIR})
add_library(pipeworks-interface INTERFACE)


target_include_directories(pipeworks-interface INTERFACE $<INSTALL_INTERFACE:include>)
target_link_libraries(pipeworks-interface INTERFACE SDL2 png sndfile)

install(TARGETS pipeworks-interface EXPORT pipeworks)

target_link_libraries(pipeworks-objects PRIVATE pipeworks-interface)


set_target_properties(pipeworks-objects PROPERTIES C_STANDARD 11
	 POSITION_INDEPENDENT_CODE ON)
if(PW_BUILD_SHARED)
target_compile_definitions(pipeworks-objects PRIVATE PIPEWORKS_BUILDSHARED)
endif()

if(PW_BUILD_SHARED)
message(STATUS "libpipeworks: Building Pipeworks Shared Library")
add_library(pipeworks-shared SHARED $<TARGET_OBJECTS:pipeworks-objects>)
target_link_libraries(pipeworks-shared pipeworks-interface)
set_target_properties(pipeworks-shared PROPERTIES OUTPUT_NAME "pipeworks")
set_target_properties(pipeworks-shared PROPERTIES SOVERSION 0.1.0)
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
target_link_libraries(pipeworks-static pipeworks-interface)
if(NOT WIN32)
set_target_properties(pipeworks-static PROPERTIES OUTPUT_NAME "pipeworks")
else()
set_target_properties(pipeworks-static PROPERTIES OUTPUT_NAME "pipeworks_static")
endif()
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
