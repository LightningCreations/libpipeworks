cmake_minimum_required(VERSION 3.15)
project(libpipeworks C)


message(STATUS "Building libpipeworks")

set(PNG_BUILD_ZLIB ON CACHE BOOL "Pipeworks uses internal ZLib by default")
set(ZLIB_LIBRARIES zlib)
set(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/zlib ${CMAKE_CURRENT_BINARY_DIR}/zlib)
set(PIPEWORKS_SDL_ROOTDIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL)
set(PIPEWORKS_PNG_ROOTDIR ${CMAKE_CURRENT_SOURCE_DIR}/libpng)
set(PIPEWORKS_FLAC_ROOTDIR ${CMAKE_CURRENT_SOURCE_DIR}/flac)
set(WITH_OGG OFF CACHE BOOL "Build FLAC with OGG support")

add_subdirectory(zlib EXCLUDE_FROM_ALL)
add_subdirectory(SDL EXCLUDE_FROM_ALL)
add_subdirectory(libpng EXCLUDE_FROM_ALL)
add_subdirectory(flac EXCLUDE_FROM_ALL)

add_subdirectory(pipeworks)
add_subdirectory(test_game)


install(DIRECTORY pipeworks/include/pipeworks DESTINATION include)
