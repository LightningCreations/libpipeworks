project(libpipeworks C)
cmake_minimum_required(VERSION 3.15)

message(STATUS "Building libpipeworks")

set(PNG_BUILD_ZLIB ON)
set(ZLIB_LIBRARY zlib)
set(ZLIB_INCLUDE ${CMAKE_CURRENT_SRC_DIR}/zlib)


add_subdirectory(zlib)
add_subdirectory(SDL)
add_subdirectory(libpng)
add_subdirectory(flac)


add_subdirectory(pipeworks)
add_subdirectory(test_game)


install(DIRECTORY include/pipeworks DESTINATION include)
