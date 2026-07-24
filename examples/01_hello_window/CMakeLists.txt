add_executable(01_hello_window main.c)
target_include_directories(01_hello_window PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(01_hello_window PRIVATE slim_core)
set_target_properties(01_hello_window PROPERTIES OUTPUT_NAME "sfx_hello_window")