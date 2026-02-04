add_executable(basic_game game.c player.c scene1.c camera.c)
target_link_libraries(basic_game PRIVATE metemengine)
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
