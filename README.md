# SlimFX

A "Vulkan-simplified" graphics library on **OpenGL 3.3 Core** with a custom shader language that transpiles to GLSL 330.

> **Status:** very early. `slim_core` is functional (window + context + input + tiny GL helpers). `slim_gfx` and `slim_shader` are stubs and will be filled in step by step.

## Repository layout

```
slimfx/
  CMakeLists.txt
  CMakePresets.json
  include/slimfx/          -- public headers (sfx_*.h)
  src/slim_core/           -- window, input, GL helpers
  src/slim_gfx/            -- pipelines, buffers, passes (WIP)
  src/slim_shader/         -- SFX shader compiler (WIP)
  third_party/             -- vendored GLFW, GLAD (you provide)
  examples/                -- 01_hello_window, 02_clear_color
```

## Building

### 1. Vendoring third-party

You need to drop two things into `third_party/`:

- **GLFW 3.3+** as a CMake subproject:
  ```
  third_party/glfw/CMakeLists.txt   (from upstream)
  third_party/glfw/include/...
  third_party/glfw/src/...
  ```
  Clone: `git clone --depth 1 --branch 3.4 https://github.com/glfw/glfw third_party/glfw`

- **GLAD** generated for *OpenGL 3.3, Core profile*:
  Use https://glad.dav1d.de with options:
  - API: OpenGL 3.3
  - Profile: Core
  - Generate a loader (not just headers)
  - Output language: C/C++
  Drop the result so that:
  ```
  third_party/glad/include/glad/gl.h
  third_party/glad/include/KHR/khrplatform.h
  third_party/glad/src/gl.c
  ```
  And we also need a `third_party/glad/CMakeLists.txt`:
  ```cmake
  add_library(glad STATIC src/gl.c)
  target_include_directories(glad PUBLIC include)
  ```

### 2. Configure & build

```sh
cmake --preset debug
cmake --build build/debug
```

Run the examples:
```sh
./build/debug/examples/01_hello_window/sfx_hello_window.exe
./build/debug/examples/02_clear_color/sfx_clear_color.exe
```

## Public API (current)

```c
#include <sfx_window.h>
#include <sfx_gl_api.h>

sfx_window_desc_t desc = {
    .title = "demo", .width = 960, .height = 540,
    .resizable = 1, .samples = 4, .vsync = 1
};
sfx_window_t* win;
sfx_window_create(&desc, &win);

while (!sfx_window_should_close(win)) {
    sfx_window_poll(win);
    sfx_gl_clear(0.1f, 0.1f, 0.1f, 1.0f);
    sfx_window_swap_buffers(win);
}
sfx_window_destroy(win);
```

## Roadmap

- [x] A. Project skeleton + slim_core (window, context, input, GL helpers)
- [ ] C. `slim_gfx` API design + implementation (pipeline, buffer, texture, pass)
- [ ] B. `slim_shader` language + transpiler to GLSL 330
- [ ] Compute shaders, instancing, MSAA config, render targets
- [ ] Hot-reload, debug UI, asset loader