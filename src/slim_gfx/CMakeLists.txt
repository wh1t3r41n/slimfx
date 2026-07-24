# slim_gfx -- pipelines, buffers, passes (Vulkan-simplified on GL 3.3)
add_library(slim_gfx STATIC sfx_gfx_stub.c)
add_library(slimfx::slim_gfx ALIAS slim_gfx)

target_include_directories(slim_gfx
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_SOURCE_DIR}/include/slimfx
)
target_link_libraries(slim_gfx PUBLIC slim_core)