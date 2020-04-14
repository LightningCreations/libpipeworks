project(libpipeworks C)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(PNG_BUILD_ZLIB ${CMAKE_CURRENT_SRC_DIR}/zlib)
set(ZLIB_LIBRARY zlib)
set(ZLIB_INCLUDE ${CMAKE_CURRENT_SRC_DIR}/zlib)

include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/SDL/include)
include_directories(SDL/include)
include_directories(libpng)

add_subdirectory(zlib)
add_subdirectory(SDL)
add_subdirectory(libpng)
add_subdirectory(flac)


add_subdirectory(pipeworks)
add_subdirectory(test_game)


install(DIRECTORY include/pipeworks DESTINATION include)
