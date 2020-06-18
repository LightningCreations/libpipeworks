cmake_minimum_required(VERSION 3.12)
project(libpipeworks C)


message(STATUS "Building libpipeworks")

option(PIPEWORKS_USE_SYSTEM_LIBRARIES "Blanket option to use system libraries by default" OFF)
mark_as_advanced(PIPEWORKS_USE_SYSTEM_LIBRARIES)

option(PIPEWORKS_USE_SYSTEM_LIBPING "Use System libpng rather than building it in pipeworks" ${PIPEWORKS_USE_SYSTEM_LIBRARIES})
option(PIPEWORKS_USE_SYSTEM_SDL "Use the system libSDL2 rather than building it" ${PIPEWORKS_USE_SYSTEM_LIBRARIES})
option(PIPEWORKS_USE_SYSTEM_LIBFLAC "Use the system libFLAC rather than building it" ${PIPEWORKS_USE_SYSTEM_LIBRARIES})


if(NOT PIPEWORKS_USE_SYSTEM_LIBPNG)
	set(PNG_BUILD_ZLIB ON CACHE BOOL "Pipeworks uses internal ZLib by default")
	set(ZLIB_LIBRARIES zlib)
	set(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/zlib ${CMAKE_CURRENT_BINARY_DIR}/zlib)
	set(PIPEWORKS_PNG_ROOTDIR ${CMAKE_CURRENT_SOURCE_DIR}/libpng)
	add_subdirectory(zlib)
	add_subdirectory(libpng)
else()
	find_package(libpng)
endif()

if(NOT PIPEWORKS_USE_SYSTEM_SDL)
	add_subdirectory(SDL)
	set(SDL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/SDL/include)
else()
	find_package(SDL)
endif()

if(NOT PIPEWORKS_USE_SYSTEM_LIBFLAC)
set(PIPEWORKS_FLAC_ROOTDIR ${CMAKE_CURRENT_SOURCE_DIR}/flac)
set(WITH_OGG OFF CACHE BOOL "Build FLAC with OGG support")
add_subdirectory(flac)
else()
	find_package(FLAC)
endif()

add_subdirectory(pipeworks)
add_subdirectory(test_game)


install(DIRECTORY pipeworks/include/pipeworks DESTINATION include)
