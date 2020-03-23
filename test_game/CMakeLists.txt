add_executable(test_game src/main.c)
add_dependencies(test_game pipeworks)
target_link_libraries(test_game pipeworks)
