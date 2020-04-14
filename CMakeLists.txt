project(libpipeworks C)
cmake_minimum_required(VERSION 3.10)

include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/SDL/include)
include_directories(SDL/include)
include_directories(libpng)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/flac)
include_directories(flac/include)


add_subdirectory(SDL)
add_subdirectory(libpng)
add_subdirectory(flac)


add_subdirectory(pipeworks)
add_subdirectory(test_game)


install(DIRECTORY include/pipeworks DESTINATION include)
