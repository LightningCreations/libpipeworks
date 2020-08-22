cmake_minimum_required(VERSION 3.12)
project(libpipeworks C)

message(STATUS "Building libpipeworks")

option(PIPEWORKS_USE_SYSTEM_LIBRARIES "Blanket option to use system libraries by default" OFF)
mark_as_advanced(PIPEWORKS_USE_SYSTEM_LIBRARIES)

option(PIPEWORKS_USE_SYSTEM_SDL "Use the system libSDL2 rather than building it" ${PIPEWORKS_USE_SYSTEM_LIBRARIES})

if(NOT PIPEWORKS_USE_SYSTEM_SDL)
	add_subdirectory(SDL)
else()
	find_package(SDL2)
	add_library(SDL2 ALIAS SDL2::SDL2)
endif()

if(PIPEWORKS_CLANG_TIDY)
    set(CMAKE_C_CLANG_TIDY ${PIPEWORKS_CLANG_TIDY} -checks=bugprone-*,clang-analyzer-*,-clang-analyzer-cplusplus* -warnings-as-errors=*)
endif()

add_subdirectory(pipeworks)
add_subdirectory(test_game)

install(DIRECTORY pipeworks/include/pipeworks DESTINATION include)
