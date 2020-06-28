cmake_minimum_required(VERSION 3.12)
project(libpipeworks C)


message(STATUS "Building libpipeworks")

option(PIPEWORKS_USE_SYSTEM_LIBRARIES "Blanket option to use system libraries by default" OFF)
mark_as_advanced(PIPEWORKS_USE_SYSTEM_LIBRARIES)

option(PIPEWORKS_USE_SYSTEM_LIBPNG "Use System libpng rather than building it in pipeworks" ${PIPEWORKS_USE_SYSTEM_LIBRARIES})
option(PIPEWORKS_USE_SYSTEM_SDL "Use the system libSDL2 rather than building it" ${PIPEWORKS_USE_SYSTEM_LIBRARIES})
option(PIPEWORKS_USE_SYSTEM_LIBSNDFILE "Use the system libsndfile rather than building it" OFF)

if(NOT PIPEWORKS_USE_SYSTEM_LIBPNG)
	set(PNG_BUILD_ZLIB ON CACHE BOOL "Pipeworks uses internal ZLib by default")
	set(ZLIB_LIBRARIES zlib)
	set(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/zlib ${CMAKE_CURRENT_BINARY_DIR}/zlib)
	set(PIPEWORKS_PNG_ROOTDIR ${CMAKE_CURRENT_SOURCE_DIR}/libpng)
	add_subdirectory(zlib)
	add_subdirectory(libpng)
else()
	find_package(PNG)
endif()

if(NOT PIPEWORKS_USE_SYSTEM_SDL)
	add_subdirectory(SDL)
else()
	find_package(SDL2)
	add_library(SDL2 ALIAS SDL2::SDL2)
endif()

if(NOT PIPEWORKS_USE_SYSTEM_LIBSNDFILE)
	add_subdirectory(libsndfile EXCLUDE_FROM_ALL)
else()
	find_package(SndFile)
endif()

if(PIPEWORKS_CLANG_TIDY)
    set(CMAKE_C_CLANG_TIDY ${PIPEWORKS_CLANG_TIDY} -checks=bugprone-*,clang-analyzer-*,-clang-analyzer-cplusplus* -warnings-as-errors=*)
endif()

add_subdirectory(pipeworks)
add_subdirectory(test_game)


install(DIRECTORY pipeworks/include/pipeworks DESTINATION include)
