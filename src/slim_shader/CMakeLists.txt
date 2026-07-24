# slim_shader -- SlimFX shader language (lexer, parser, GLSL 330 transpiler)
add_library(slim_shader STATIC sfx_shader_stub.c)
add_library(slimfx::slim_shader ALIAS slim_shader)

target_include_directories(slim_shader
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_link_libraries(slim_shader PUBLIC slim_core)