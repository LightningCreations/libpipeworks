# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/vc/lib")

add_executable(test_game src/main.c)
target_link_libraries(test_game pipeworks)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/menu DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(../pipeworks/include)
