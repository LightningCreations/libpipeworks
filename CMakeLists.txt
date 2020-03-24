project(libpipeworks C)
cmake_minimum_required(VERSION 3.10)

include_directories(include)

add_subdirectory(pipeworks)
add_subdirectory(test_game)

install(DIRECTORIES include DESTINATION include)
