project(libpipeworks CXX)
cmake_minimum_required(VERSION 3.10)

include_directories(include util/collect/include)

add_subdirectory(util/collect)

add_library(pipeworks SHARED src/engine.c src/game.c util/collect)
