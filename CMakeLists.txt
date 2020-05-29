project(libpipeworks C)
cmake_minimum_required(VERSION 3.15)

message(STATUS "Building libpipeworks")

set(PNG_BUILD_ZLIB ON CACHE BOOL "Pipeworks uses internal ZLib by default")
set(ZLIB_LIBRARIES zlib)
set(ZLIB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/zlib ${CMAKE_CURRENT_BINARY_DIR}/zlib)
set(WITH_OGG OFF CACHE BOOL "Build FLAC with OGG support")
if(WIN32)
set(PNG_SHARED OFF CACHE BOOL "Pipeworks statically links internal libpng by default on windows")
endif()

add_subdirectory(zlib EXCLUDE_FROM_ALL)
add_subdirectory(SDL EXCLUDE_FROM_ALL)
add_subdirectory(libpng EXCLUDE_FROM_ALL)
add_subdirectory(flac EXCLUDE_FROM_ALL)

add_subdirectory(pipeworks)
add_subdirectory(test_game)


install(DIRECTORY include/pipeworks DESTINATION include)
