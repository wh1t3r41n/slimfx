# slim_core -- window, context, input, our own GL 3.3 loader, public GL helpers
add_library(slim_core STATIC
    sfx_window.c
    sfx_gl.c
    sfx_gl_api.c
)
add_library(slimfx::slim_core ALIAS slim_core)

target_include_directories(slim_core
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    PUBLIC  ${CMAKE_SOURCE_DIR}/include    # multi-config workaround (MSVC vcxproj)
    PRIVATE ${CMAKE_SOURCE_DIR}/include/slimfx
)

target_link_libraries(slim_core PUBLIC glfw)

if(WIN32 AND NOT MSVC)
    target_link_libraries(slim_core PUBLIC gdi32)
endif()

if(MSVC)
    target_link_libraries(slim_core PRIVATE user32 gdi32)
endif()