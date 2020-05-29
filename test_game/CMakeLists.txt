# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/vc/lib")

set(CMAKE_C_FLAGS "-g")

add_executable(test_game src/main.c)
add_dependencies(test_game pipeworks)
target_link_libraries(test_game pipeworks)
include_directories(../pipeworks/include)
