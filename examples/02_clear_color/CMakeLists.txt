add_executable(02_clear_color main.c)
target_include_directories(02_clear_color PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(02_clear_color PRIVATE slim_core slim_gfx)
set_target_properties(02_clear_color PROPERTIES OUTPUT_NAME "sfx_clear_color")