project(libpipeworks CXX)
cmake_minimum_required(VERSION 3.10)

include_directories(include)

add_library(pipeworks SHARED src/engine.c src/game.c)
