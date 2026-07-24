cmake_minimum_required(VERSION 3.21)
project(slimfx
    VERSION 0.1.0
    DESCRIPTION "Vulkan-simplified graphics library on OpenGL 3.3"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# --- Warnings ---------------------------------------------------------------
if(MSVC)
    add_compile_options(/W4 /utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)
endif()

# --- Options ----------------------------------------------------------------
option(SFX_BUILD_EXAMPLES  "Build slimfx example apps"  ON)
option(SFX_BUILD_SHADERS   "Build slim_shader compiler" ON)
option(SFX_USE_SYSTEM_GLFW "Use system GLFW via find_package" OFF)

# Make <sfx_*.h> resolvable from every target without per-target boilerplate.
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/slimfx)  # for internal/sfx_gl.h

# --- Third-party ------------------------------------------------------------
set(SFX_THIRD_PARTY ${CMAKE_SOURCE_DIR}/third_party)

if(SFX_USE_SYSTEM_GLFW)
    find_package(glfw3 REQUIRED)
    if(NOT TARGET glfw)
        # Some finders create glfw instead of glfw3
        add_library(glfw ALIAS glfw3)
    endif()
else()
    # Bundle GLFW
    set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_SHARED_LIBRARY OFF CACHE BOOL "" FORCE)
    add_subdirectory(${SFX_THIRD_PARTY}/glfw ${CMAKE_BINARY_DIR}/_glfw EXCLUDE_FROM_ALL)
endif()

# --- Libraries --------------------------------------------------------------
add_subdirectory(src/slim_core)
add_subdirectory(src/slim_gfx)
if(SFX_BUILD_SHADERS)
    add_subdirectory(src/slim_shader)
endif()

# --- Examples ----------------------------------------------------------------
if(SFX_BUILD_EXAMPLES)
    add_subdirectory(examples/01_hello_window)
    add_subdirectory(examples/02_clear_color)
endif()